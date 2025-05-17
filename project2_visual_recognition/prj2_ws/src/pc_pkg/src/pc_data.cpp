#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/transforms.hpp>

#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

class PointCloudDetectNode : public rclcpp::Node
{
public:
  PointCloudDetectNode()
  : Node("pointcloud_objects_node")
  {
    // 初始化 TF
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    // 订阅点云
    pc_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/kinect2/sd/points",
      10,
      std::bind(&PointCloudDetectNode::pointCloudCallback, this, std::placeholders::_1)
    );
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pc_sub_;
  tf2_ros::Buffer::SharedPtr tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  void pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    // 等待 TF 可用
    if (!tf_buffer_->canTransform("base_footprint", msg->header.frame_id, tf2::TimePointZero, tf2::durationFromSec(1.0))) {
      RCLCPP_WARN(this->get_logger(), "TF transform not available: %s -> base_footprint", msg->header.frame_id.c_str());
      return;
    }

    // 变换点云至 base_footprint 坐标系
    sensor_msgs::msg::PointCloud2 pc_transformed;
    try {
      pcl_ros::transformPointCloud("base_footprint", *msg, pc_transformed, *tf_buffer_);
    } catch (const tf2::TransformException &ex) {
      RCLCPP_ERROR(this->get_logger(), "Transform error: %s", ex.what());
      return;
    }

    // ROS 点云转 PCL 格式
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(pc_transformed, cloud);

    // 通过滤波裁剪兴趣区域
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud.makeShared());
    pass.setFilterFieldName("x");
    pass.setFilterLimits(0.5, 1.5);
    pass.filter(cloud);

    pass.setInputCloud(cloud.makeShared());
    pass.setFilterFieldName("y");
    pass.setFilterLimits(-0.5, 0.5);
    pass.filter(cloud);

    pass.setInputCloud(cloud.makeShared());
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.5, 1.5);
    pass.filter(cloud);

    // 平面分割（用于去除地面或背景）
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr plane_indices(new pcl::PointIndices);
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.05);
    seg.setInputCloud(cloud.makeShared());
    seg.segment(*plane_indices, *coefficients);

    // 计算平面高度（平均 z）
    if (plane_indices->indices.empty()) {
      RCLCPP_WARN(this->get_logger(), "No plane found.");
      return;
    }

    float sum_z = 0.0;
    for (int idx : plane_indices->indices) {
      sum_z += cloud.points[idx].z;
    }
    float plane_height = sum_z / plane_indices->indices.size();
    RCLCPP_INFO(this->get_logger(), "Plane height: %.2f", plane_height);

    // 滤除低于平面以上一定高度的点（物体候选）
    pass.setInputCloud(cloud.makeShared());
    pass.setFilterFieldName("z");
    pass.setFilterLimits(plane_height + 0.2, 1.5);
    pass.filter(cloud);

    // 聚类提取独立物体
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud.makeShared());

    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setInputCloud(cloud.makeShared());
    ec.setSearchMethod(tree);
    ec.setClusterTolerance(0.1);
    ec.setMinClusterSize(100);
    ec.setMaxClusterSize(25000);

    std::vector<pcl::PointIndices> cluster_indices;
    ec.extract(cluster_indices);

    RCLCPP_INFO(this->get_logger(), "Detected %zu object(s)", cluster_indices.size());

    // 计算每个物体质心
    for (size_t i = 0; i < cluster_indices.size(); ++i) {
      float sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
      int count = cluster_indices[i].indices.size();
      for (int idx : cluster_indices[i].indices) {
        sum_x += cloud.points[idx].x;
        sum_y += cloud.points[idx].y;
        sum_z += cloud.points[idx].z;
      }
      RCLCPP_INFO(this->get_logger(), "Object %zu: Position = (%.2f, %.2f, %.2f)",
                  i, sum_x / count, sum_y / count, sum_z / count);
    }
    RCLCPP_INFO(this->get_logger(), "------------------------------");
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointCloudDetectNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

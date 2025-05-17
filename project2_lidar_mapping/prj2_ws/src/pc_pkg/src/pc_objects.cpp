#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

#include <tf2_ros/transform_listener.h>
#include <pcl_ros/transforms.hpp>

#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

class PointCloudObjectsNode : public rclcpp::Node
{
public:
  PointCloudObjectsNode()
  : Node("pointcloud_objects_node")
  {
    // 初始化TF监听器
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    // 声明参数并设置默认值
    this->declare_parameter<double>("filter_x_min", 0.5);
    this->declare_parameter<double>("filter_x_max", 1.5);
    this->declare_parameter<double>("filter_y_min", -0.5);
    this->declare_parameter<double>("filter_y_max", 0.5);
    this->declare_parameter<double>("filter_z_min", 0.5);
    this->declare_parameter<double>("filter_z_max", 1.5);
    this->declare_parameter<double>("plane_distance_threshold", 0.05);
    this->declare_parameter<int>("cluster_min_size", 100);
    this->declare_parameter<int>("cluster_max_size", 25000);
    this->declare_parameter<double>("cluster_tolerance", 0.1);
    this->declare_parameter<double>("height_above_plane", 0.2);

    // 订阅点云话题
    pc_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/kinect2/sd/points", 1,
      std::bind(&PointCloudObjectsNode::pointCloudCallback, this, std::placeholders::_1));
  }

private:
  void pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    // 判断是否能转换到base_footprint坐标系
    if (!tf_buffer_->canTransform("base_footprint", msg->header.frame_id, msg->header.stamp)) {
      RCLCPP_WARN(this->get_logger(), "Cannot transform from %s to base_footprint at time %u.%u",
                  msg->header.frame_id.c_str(), msg->header.stamp.sec, msg->header.stamp.nanosec);
      return;
    }

    // 坐标变换
    sensor_msgs::msg::PointCloud2 pc_transformed;
    pcl_ros::transformPointCloud("base_footprint", *msg, pc_transformed, *tf_buffer_);

    // 转换成PCL格式
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(pc_transformed, *cloud);

    // 读取滤波参数
    double x_min, x_max, y_min, y_max, z_min, z_max;
    this->get_parameter("filter_x_min", x_min);
    this->get_parameter("filter_x_max", x_max);
    this->get_parameter("filter_y_min", y_min);
    this->get_parameter("filter_y_max", y_max);
    this->get_parameter("filter_z_min", z_min);
    this->get_parameter("filter_z_max", z_max);

    // PassThrough滤波器
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);

    pass.setFilterFieldName("x");
    pass.setFilterLimits(x_min, x_max);
    pass.filter(*cloud);

    pass.setInputCloud(cloud);
    pass.setFilterFieldName("y");
    pass.setFilterLimits(y_min, y_max);
    pass.filter(*cloud);

    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(z_min, z_max);
    pass.filter(*cloud);

    if (cloud->empty()) {
      RCLCPP_WARN(this->get_logger(), "Filtered cloud is empty.");
      return;
    }

    // 平面分割
    double distance_threshold;
    this->get_parameter("plane_distance_threshold", distance_threshold);

    pcl::SACSegmentation<pcl::PointXYZ> seg;
    seg.setInputCloud(cloud);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(distance_threshold);
    seg.setOptimizeCoefficients(true);

    pcl::PointIndices::Ptr plane_inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    seg.segment(*plane_inliers, *coefficients);

    if (plane_inliers->indices.empty()) {
      RCLCPP_WARN(this->get_logger(), "No planar model found.");
      return;
    }

    // 计算平面高度（Z轴平均值）
    float z_sum = 0;
    for (auto idx : plane_inliers->indices) {
      z_sum += cloud->points[idx].z;
    }
    float plane_height = z_sum / plane_inliers->indices.size();
    RCLCPP_INFO(this->get_logger(), "Detected plane height: %.3f", plane_height);

    // 高于平面一定高度的点过滤
    double height_above_plane;
    this->get_parameter("height_above_plane", height_above_plane);

    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(plane_height + height_above_plane, z_max);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_objects(new pcl::PointCloud<pcl::PointXYZ>);
    pass.filter(*cloud_objects);

    if (cloud_objects->empty()) {
      RCLCPP_WARN(this->get_logger(), "No points found above plane.");
      return;
    }

    // 聚类提取
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud_objects);

    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setInputCloud(cloud_objects);

    int cluster_min_size, cluster_max_size;
    double cluster_tolerance;
    this->get_parameter("cluster_min_size", cluster_min_size);
    this->get_parameter("cluster_max_size", cluster_max_size);
    this->get_parameter("cluster_tolerance", cluster_tolerance);

    ec.setMinClusterSize(cluster_min_size);
    ec.setMaxClusterSize(cluster_max_size);
    ec.setClusterTolerance(cluster_tolerance);
    ec.setSearchMethod(tree);

    std::vector<pcl::PointIndices> cluster_indices;
    ec.extract(cluster_indices);

    RCLCPP_INFO(this->get_logger(), "Detected %zu object clusters", cluster_indices.size());

    // 输出每个物体质心位置
    for (size_t i = 0; i < cluster_indices.size(); ++i) {
      const auto& indices = cluster_indices[i];
      float sum_x = 0, sum_y = 0, sum_z = 0;
      for (auto idx : indices.indices) {
        const auto& pt = cloud_objects->points[idx];
        sum_x += pt.x;
        sum_y += pt.y;
        sum_z += pt.z;
      }
      float centroid_x = sum_x / indices.indices.size();
      float centroid_y = sum_y / indices.indices.size();
      float centroid_z = sum_z / indices.indices.size();

      RCLCPP_INFO(this->get_logger(), "Object %zu centroid: [%.3f, %.3f, %.3f]", i, centroid_x, centroid_y, centroid_z);
    }

    RCLCPP_INFO(this->get_logger(), "-----------------------");
  }

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pc_sub_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointCloudObjectsNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

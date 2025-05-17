/**
 * @file lidar_data.cpp
 * @author Danny Lee (20213041@cqu.edu.cn)
 * @brief LIDAR数据处理节点 - 读取激光雷达数据并计算正前方障碍物距离
 * @version 1.0
 * @date 2025-5-18
 * 
 * @copyright Copyright (c) 2025
 * 
 * 功能描述：
 * 1. 订阅ROS 2的LaserScan话题(/scan)
 * 2. 计算激光雷达正前方距离(取扫描数据的中间点)
 * 3. 进行数据有效性检查(空数据/无限值/非法值/范围检查)
 * 4. 输出带角度信息的距离测量结果
 * 
 * 订阅话题：
 *   /scan (sensor_msgs/msg/LaserScan) - 激光雷达扫描数据
 * 
 * 参数配置：
 *   无(可通过修改代码调整中心点计算方式)
 * 
 * 日志输出示例：
 *   [INFO] 正前方距离: 1.25米 (角度: 0.0°)
 *   [WARN] 正前方距离超出有效范围: 25.00米
 */

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

class LidarNode : public rclcpp::Node
{
public:
    LidarNode() : Node("lidar_processing_node")
    {
        // 初始化LIDAR订阅器
        lidar_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 
            rclcpp::SensorDataQoS(),  // 使用适合传感器数据的QoS配置
            std::bind(&LidarNode::scanCallback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "LIDAR处理节点已初始化");
    }

private:
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // 数据有效性检查
        if (msg->ranges.empty()) {
            RCLCPP_WARN(this->get_logger(), "接收到空扫描数据");
            return;
        }

        // 计算正前方距离(取中间点)
        const size_t center_index = msg->ranges.size() / 2;
        const float center_distance = msg->ranges[center_index];

        // 数据合理性检查
        if (std::isinf(center_distance)) {
            RCLCPP_WARN(this->get_logger(), "正前方距离无限远");
            return;
        }
        if (std::isnan(center_distance)) {
            RCLCPP_WARN(this->get_logger(), "正前方距离数据无效");
            return;
        }
        if (center_distance < msg->range_min || center_distance > msg->range_max) {
            RCLCPP_WARN(this->get_logger(), "正前方距离超出有效范围: %.2f米", center_distance);
            return;
        }

        // 输出处理结果
        RCLCPP_INFO(this->get_logger(), 
                   "正前方距离: %.2f米 (角度: %.1f°)",
                   center_distance,
                   msg->angle_min + center_index * msg->angle_increment);
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_sub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LidarNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
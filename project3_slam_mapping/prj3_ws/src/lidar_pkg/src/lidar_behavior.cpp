/**
 * @file lidar_data.cpp
 * @author Danny Lee (20213041@cqu.edu.cn)
 * @brief LIDAR避障行为控制节点
 * @version 1.0
 * @date 2025-5-18
 * 
 * @copyright Copyright (c) 2025
 * 功能描述：
 * 1. 订阅激光雷达数据(/scan)
 * 2. 检测正前方障碍物距离
 * 3. 根据距离实施避障策略：
 *    - 距离<1.5米时：旋转避障(0.3 rad/s)
 *    - 距离≥1.5米时：前进(0.1 m/s)
 * 4. 避障动作持续周期控制(100次回调)
 */

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

class LidarAvoidanceNode : public rclcpp::Node
{
public:
    LidarAvoidanceNode() 
    : Node("lidar_avoidance_node"),
      obstacle_distance_threshold_(1.5f),
      rotation_speed_(0.3),
      forward_speed_(0.1),
      avoidance_duration_(100),
      remaining_avoidance_cycles_(0)
    {
        // 初始化速度指令发布器
        cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        
        // 初始化LIDAR订阅器
        lidar_sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan",
            rclcpp::SensorDataQoS(),
            std::bind(&LidarAvoidanceNode::scanCallback, this, std::placeholders::_1));
            
        RCLCPP_INFO(get_logger(), "LIDAR避障节点已启动");
    }

private:
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // 获取正前方距离
        const size_t center_index = msg->ranges.size() / 2;
        const float front_distance = msg->ranges[center_index];
        
        RCLCPP_INFO(get_logger(), "正前方距离: %.2f 米", front_distance);

        // 检查是否处于避障周期
        if (remaining_avoidance_cycles_ > 0) {
            remaining_avoidance_cycles_--;
            return;
        }

        // 生成控制指令
        geometry_msgs::msg::Twist cmd_vel;
        
        if (front_distance < obstacle_distance_threshold_) {
            cmd_vel.angular.z = rotation_speed_;  // 旋转避障
            remaining_avoidance_cycles_ = avoidance_duration_;
            RCLCPP_WARN(get_logger(), "检测到障碍物，开始避障旋转");
        } else {
            cmd_vel.linear.x = forward_speed_;  // 前进
        }

        // 发布控制指令
        cmd_vel_pub_->publish(cmd_vel);
    }

    // ROS2接口
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_sub_;

    // 控制参数
    const float obstacle_distance_threshold_;  // 障碍物判定阈值(米)
    const float rotation_speed_;              // 避障旋转速度(rad/s)
    const float forward_speed_;               // 前进速度(m/s)
    const int avoidance_duration_;            // 避障持续时间(回调周期数)
    
    // 状态变量
    int remaining_avoidance_cycles_;          // 剩余避障周期计数
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LidarAvoidanceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
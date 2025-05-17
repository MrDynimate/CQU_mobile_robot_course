#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

class IMUBehaviorNode : public rclcpp::Node
{
public:
    IMUBehaviorNode() : Node("imu_behavior_node"), target_yaw_(90.0), linear_speed_(0.1), angular_gain_(0.01)
    {
        // Initialize subscriber and publisher
        imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
            "imu", 
            10, 
            std::bind(&IMUBehaviorNode::imuCallback, this, std::placeholders::_1));
            
        cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

private:
    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        // Convert quaternion to Euler angles
        tf2::Quaternion tf2_quaternion(
            msg->orientation.x,
            msg->orientation.y,
            msg->orientation.z,
            msg->orientation.w);
            
        tf2::Matrix3x3 matrix(tf2_quaternion);
        double roll, pitch, yaw;
        matrix.getRPY(roll, pitch, yaw);
        
        // Convert to degrees
        roll *= 180.0 / M_PI;
        pitch *= 180.0 / M_PI;
        yaw *= 180.0 / M_PI;
        
        RCLCPP_INFO(get_logger(), 
                   "Current Orientation - Roll: %.1f°, Pitch: %.1f°, Yaw: %.1f°", 
                   roll, pitch, yaw);
        
        // Calculate control command
        geometry_msgs::msg::Twist vel_msg;
        vel_msg.linear.x = linear_speed_;
        vel_msg.angular.z = angular_gain_ * (target_yaw_ - yaw);
        
        cmd_vel_pub_->publish(vel_msg);
    }
    
    // ROS 2 interfaces
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    
    // Control parameters
    const double target_yaw_;      // Target yaw angle in degrees
    const double linear_speed_;    // Constant forward speed
    const double angular_gain_;    // Proportional gain for angular control
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<IMUBehaviorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
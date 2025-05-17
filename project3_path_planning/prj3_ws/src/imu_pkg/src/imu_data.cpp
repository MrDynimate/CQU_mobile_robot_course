#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

class IMUNode : public rclcpp::Node
{
public:
    IMUNode() : Node("imu_data_node")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu", 
            10, 
            std::bind(&IMUNode::IMUCallback, this, std::placeholders::_1));
    }

private:
    void IMUCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        // 四元数转欧拉角
        tf2::Quaternion tf2_quaternion(
            msg->orientation.x,
            msg->orientation.y,
            msg->orientation.z,
            msg->orientation.w);
            
        tf2::Matrix3x3 matrix(tf2_quaternion);
        double roll, pitch, yaw;
        matrix.getRPY(roll, pitch, yaw);
        
        // 弧度转角度
        roll *= 180.0 / M_PI;
        pitch *= 180.0 / M_PI;
        yaw *= 180.0 / M_PI;
        
        RCLCPP_INFO(this->get_logger(), 
                   "Roll: %.1f°, Pitch: %.1f°, Yaw: %.1f°", 
                   roll, pitch, yaw);
    }
    
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<IMUNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
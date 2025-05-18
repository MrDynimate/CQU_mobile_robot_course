/**
 * @file waypoint_navigation.cpp
 * @author Danny Lee (20213041@cqu.edu.cn)
 * @brief 航点导航控制节点 - 发布航点并处理导航结果
 * @version 1.0
 * @date 2025-5-18
 * 功能:
 * 1. 发布导航目标航点到 /waterplus/navi_waypoint 话题
 * 2. 订阅 /waterplus/navi_result 话题获取导航结果
 * 3. 当收到"navi done"消息时，打印到达信息
 * 
 */

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <memory>

using std::placeholders::_1;

class WaypointNavigation : public rclcpp::Node
{
public:
    WaypointNavigation() 
        : Node("waypoint_navigation_node")
    {
        // 初始化发布者和订阅者
        navi_publisher_ = this->create_publisher<std_msgs::msg::String>(
            "/waterplus/navi_waypoint", 10);
            
        result_subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "/waterplus/navi_result", 10,
            std::bind(&WaypointNavigation::resultCallback, this, _1));

        // 启动1秒后发布第一个航点
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&WaypointNavigation::publishWaypoint, this));
    }

private:
    void resultCallback(const std_msgs::msg::String::SharedPtr msg)
    {
        if(msg->data == "navi done") {
            RCLCPP_INFO(this->get_logger(), "Destination reached!");
        }
    }

    void publishWaypoint()
    {
        auto message = std_msgs::msg::String();
        message.data = "1";  // 第一个航点
        navi_publisher_->publish(message);
        timer_->cancel();  // 只发布一次
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr navi_publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr result_subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<WaypointNavigation>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
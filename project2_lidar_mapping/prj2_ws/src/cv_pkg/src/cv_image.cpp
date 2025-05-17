#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber()
    : Node("cv_image_node")
    {
        using std::placeholders::_1;
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/kinect2/qhd/image_raw", 10, std::bind(&ImageSubscriber::image_callback, this, _1));
        cv::namedWindow("RGB", cv::WINDOW_AUTOSIZE);
    }

    ~ImageSubscriber()
    {
        cv::destroyAllWindows();
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            cv::imshow("RGB", cv_ptr->image);
            cv::waitKey(1);
        }
        catch (const cv_bridge::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

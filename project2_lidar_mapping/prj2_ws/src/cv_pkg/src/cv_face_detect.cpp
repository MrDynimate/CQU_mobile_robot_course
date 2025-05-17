#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/region_of_interest.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class FaceDetectorNode : public rclcpp::Node
{
public:
  FaceDetectorNode()
  : Node("cv_face_detect")
  {
    using std::placeholders::_1;

    // 创建订阅器和发布器
    rgb_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/kinect2/qhd/image_raw", 1, std::bind(&FaceDetectorNode::CamRGBCallback, this, _1));

    face_sub_ = this->create_subscription<sensor_msgs::msg::RegionOfInterest>(
      "/face_position", 1, std::bind(&FaceDetectorNode::FacePosCallback, this, _1));

    frame_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
      "/face_detector_input", 1);

    cv::namedWindow("Face");
  }

  ~FaceDetectorNode()
  {
    cv::destroyAllWindows();
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_sub_;
  rclcpp::Subscription<sensor_msgs::msg::RegionOfInterest>::SharedPtr face_sub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr frame_pub_;

  cv::Mat img_face_;  // 保存当前图像帧

  void CamRGBCallback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    try {
      cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      img_face_ = cv_ptr->image.clone();

      frame_pub_->publish(*msg);
    } catch (cv_bridge::Exception& e) {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
    }
  }

  void FacePosCallback(const sensor_msgs::msg::RegionOfInterest::SharedPtr msg)
  {
    if (img_face_.empty()) {
      RCLCPP_WARN(this->get_logger(), "Image not received yet.");
      return;
    }

    // 绘制矩形框
    cv::rectangle(img_face_,
                  cv::Point(msg->x_offset, msg->y_offset),
                  cv::Point(msg->x_offset + msg->width, msg->y_offset + msg->height),
                  cv::Scalar(0, 0, 255), 2, cv::LINE_8);

    cv::imshow("Face", img_face_);
    cv::waitKey(1);
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FaceDetectorNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
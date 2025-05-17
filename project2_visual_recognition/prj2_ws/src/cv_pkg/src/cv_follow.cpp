#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using std::placeholders::_1;
using namespace cv;

class CvFollowNode : public rclcpp::Node
{
public:
    CvFollowNode() : Node("cv_follow_node")
    {
        RCLCPP_INFO(this->get_logger(), "Starting cv_follow_node...");
        
        // 初始化阈值
        iLowH_ = 10; iHighH_ = 40;
        iLowS_ = 90; iHighS_ = 255;
        iLowV_ = 1;  iHighV_ = 255;

        // 创建图像订阅器
        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/kinect2/qhd/image_raw", 10,
            std::bind(&CvFollowNode::imageCallback, this, _1));

        // 创建窗口和滑动条
        namedWindow("Threshold", WINDOW_AUTOSIZE);
        createTrackbar("LowH", "Threshold", &iLowH_, 179);
        createTrackbar("HighH", "Threshold", &iHighH_, 179);
        createTrackbar("LowS", "Threshold", &iLowS_, 255);
        createTrackbar("HighS", "Threshold", &iHighS_, 255);
        createTrackbar("LowV", "Threshold", &iLowV_, 255);
        createTrackbar("HighV", "Threshold", &iHighV_, 255);

        namedWindow("RGB");
        namedWindow("HSV");
        namedWindow("Result");
    }

    ~CvFollowNode()
    {
        destroyAllWindows();
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        Mat img_original = cv_ptr->image;
        Mat img_hsv, img_thresholded;

        // 转换到 HSV 并均衡化 V 通道
        cvtColor(img_original, img_hsv, COLOR_BGR2HSV);
        std::vector<Mat> hsv_split;
        split(img_hsv, hsv_split);
        equalizeHist(hsv_split[2], hsv_split[2]);
        merge(hsv_split, img_hsv);

        // HSV阈值分割
        inRange(img_hsv,
                Scalar(iLowH_, iLowS_, iLowV_),
                Scalar(iHighH_, iHighS_, iHighV_),
                img_thresholded);

        // 提取质心
        int target_x = 0, target_y = 0, pixel_count = 0;
        for (int y = 0; y < img_thresholded.rows; y++) {
            for (int x = 0; x < img_thresholded.cols; x++) {
                if (img_thresholded.at<uchar>(y, x) == 255) {
                    target_x += x;
                    target_y += y;
                    pixel_count++;
                }
            }
        }

        if (pixel_count > 0) {
            target_x /= pixel_count;
            target_y /= pixel_count;

            // 绘制十字线
            line(img_original, Point(target_x - 10, target_y), Point(target_x + 10, target_y), Scalar(255, 0, 0), 2);
            line(img_original, Point(target_x, target_y - 10), Point(target_x, target_y + 10), Scalar(255, 0, 0), 2);

            RCLCPP_INFO(this->get_logger(), "Target (%d, %d), PixelCount: %d", target_x, target_y, pixel_count);
        } else {
            RCLCPP_INFO(this->get_logger(), "Target disappeared...");
        }

        // 显示图像
        imshow("RGB", img_original);
        imshow("HSV", img_hsv);
        imshow("Result", img_thresholded);
        waitKey(1);
    }

    // 成员变量
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;

    int iLowH_, iHighH_;
    int iLowS_, iHighS_;
    int iLowV_, iHighV_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CvFollowNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

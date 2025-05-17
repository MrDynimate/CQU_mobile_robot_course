#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// 全局节点指针
std::shared_ptr<rclcpp::Node> node;

// HSV参数可调
static int iLowH = 10, iHighH = 40;
static int iLowS = 90, iHighS = 255;
static int iLowV = 1, iHighV = 255;

void CamRGBCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    // 将ROS图像消息转换为OpenCV图像
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(node->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat imgOriginal = cv_ptr->image;

    // BGR转HSV
    cv::Mat imgHSV;
    cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

    // 直方图均衡化增强亮度通道
    std::vector<cv::Mat> hsvSplit;
    cv::split(imgHSV, hsvSplit);
    cv::equalizeHist(hsvSplit[2], hsvSplit[2]);
    cv::merge(hsvSplit, imgHSV);

    // 阈值分割
    cv::Mat imgThresholded;
    cv::inRange(imgHSV, 
                cv::Scalar(iLowH, iLowS, iLowV), 
                cv::Scalar(iHighH, iHighS, iHighV), 
                imgThresholded);

    // 形态学处理（去噪）
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(imgThresholded, imgThresholded, cv::MORPH_CLOSE, element);

    // 目标提取（质心）
    int nTargetX = 0, nTargetY = 0, nPixCount = 0;
    int nImgWidth = imgThresholded.cols;
    int nImgHeight = imgThresholded.rows;

    for (int y = 0; y < nImgHeight; ++y) {
        for (int x = 0; x < nImgWidth; ++x) {
            if (imgThresholded.at<uchar>(y, x) == 255) {
                nTargetX += x;
                nTargetY += y;
                nPixCount++;
            }
        }
    }

    // 绘制目标位置
    if (nPixCount > 0) {
        nTargetX /= nPixCount;
        nTargetY /= nPixCount;
        printf("Target (%d, %d) PixelCount = %d\n", nTargetX, nTargetY, nPixCount);

        cv::Point line_begin(nTargetX - 10, nTargetY);
        cv::Point line_end(nTargetX + 10, nTargetY);
        cv::line(imgOriginal, line_begin, line_end, cv::Scalar(255, 0, 0));

        line_begin = cv::Point(nTargetX, nTargetY - 10);
        line_end   = cv::Point(nTargetX, nTargetY + 10);
        cv::line(imgOriginal, line_begin, line_end, cv::Scalar(255, 0, 0));
    } else {
        printf("Target disappeared...\n");
    }

    // 显示窗口
    cv::imshow("RGB", imgOriginal);
    cv::imshow("HSV", imgHSV);
    cv::imshow("Result", imgThresholded);
    cv::waitKey(5);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    node = std::make_shared<rclcpp::Node>("cv_hsv_node");

    // 订阅图像话题
    auto rgb_sub = node->create_subscription<sensor_msgs::msg::Image>(
        "/kinect2/qhd/image_raw", 10, CamRGBCallback);

    // 创建调节条窗口
    cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("LowH", "Threshold", &iLowH, 179);
    cv::createTrackbar("HighH", "Threshold", &iHighH, 179);
    cv::createTrackbar("LowS", "Threshold", &iLowS, 255);
    cv::createTrackbar("HighS", "Threshold", &iHighS, 255);
    cv::createTrackbar("LowV", "Threshold", &iLowV, 255);
    cv::createTrackbar("HighV", "Threshold", &iHighV, 255);

    // 显示窗口初始化
    cv::namedWindow("RGB");
    cv::namedWindow("HSV");
    cv::namedWindow("Result");

    // 主循环
    rclcpp::spin(node);
    cv::destroyAllWindows();
    rclcpp::shutdown();
    return 0;
}

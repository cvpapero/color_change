#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";
using namespace std;

class ImageConverter
{
  ros::NodeHandle nh_;
  ros::Subscriber sub;

public:
  ImageConverter()
  {
    sub = nh_.subscribe("/speed", 1, 
			&ImageConverter::imageCb, this);


    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const std_msgs::Float64::ConstPtr& msg)
  {
    double c = msg->data*255/50;
    cout << "msg: "<<msg->data << ", color: "<<c <<endl;
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
    // Blue，塗りつぶし，アンチエイリアス
    cv::rectangle(img, cv::Point(0,0), cv::Point(500, 500), cv::Scalar(c,c,c), -1, CV_AA);

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, img);
    cv::waitKey(3);

  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}

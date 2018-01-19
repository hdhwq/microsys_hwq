#if 0
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
using namespace cv;
int main()
{
	// 读入一张图片（游戏原画）    
	Mat img = imread("pic.jpg");
	// 创建一个名为 "游戏原画"窗口    
	cvNamedWindow("游戏原画");
	// 在窗口中显示游戏原画    
	imshow("游戏原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
}
#endif

#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp> 
int main()
{
	//加载源图像和模板图像  
	cv::Mat image_source = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat image_template = cv::imread("template.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat image_matched;

	//模板匹配  
	cv::matchTemplate(image_source, image_template, image_matched, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置  
	cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);

	cv::Mat image_color;
	cv::cvtColor(image_source, image_color, CV_GRAY2BGR);
	cv::circle(image_color,
		cv::Point(maxLoc.x + image_template.cols / 2, maxLoc.y + image_template.rows / 2),
		20,
		cv::Scalar(0, 0, 255),
		2,
		8,
		0);

	cv::imshow("source image", image_source);
	cv::imshow("match result", image_matched);
	cv::imshow("target", image_color);
	cv::waitKey(0);

	return 0;
}
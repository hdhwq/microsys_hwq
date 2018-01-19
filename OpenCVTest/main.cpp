#if 0
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
using namespace cv;
int main()
{
	// ����һ��ͼƬ����Ϸԭ����    
	Mat img = imread("pic.jpg");
	// ����һ����Ϊ "��Ϸԭ��"����    
	cvNamedWindow("��Ϸԭ��");
	// �ڴ�������ʾ��Ϸԭ��    
	imshow("��Ϸԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
}
#endif

#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp> 
int main()
{
	//����Դͼ���ģ��ͼ��  
	cv::Mat image_source = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat image_template = cv::imread("template.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat image_matched;

	//ģ��ƥ��  
	cv::matchTemplate(image_source, image_template, image_matched, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//Ѱ�����ƥ��λ��  
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
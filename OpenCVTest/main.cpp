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

#if 0
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp> 
using namespace cv;
using namespace std;
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
	//cv::circle(image_color,
	//	cv::Point(maxLoc.x + image_template.cols / 2, maxLoc.y + image_template.rows / 2),
	//	10,
	//	cv::Scalar(0, 255, 255),
	//	2,
	//	8,
	//	0);
	cv::circle(image_color,
		maxLoc,
		2,
		cv::Scalar(0, 255, 255),
		2,
		8,
		0);


	Point c (maxLoc.x + image_template.cols / 2, maxLoc.y + image_template.rows / 2);
	Point a (c.x + 20, c.y + 15);
	Point b (c.x - 20, c.y - 20);

	cv::rectangle(image_color,
		a,b,
		cv::Scalar(0, 0, 255), 1, 1, 0
	);

	cout << "minVAL��"<<minVal <<"maxVal:"<< maxVal << endl;

	cv::imshow("source image", image_source);
	cv::imshow("match result", image_matched);
	cv::imshow("target", image_color);
	cv::waitKey(0);

	return 0;
}
#endif

#if 1
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// ȫ�ֱ���
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// ��������
void MatchingMethod(int, void*);

/** @������ */
int main(int argc, char** argv)
{
	/// ����ԭͼ���ģ���
	img = imread("lena.jpg", 1);
	templ = imread("template.jpg", 1);

	/// ��������
	namedWindow(image_window, CV_WINDOW_AUTOSIZE);
	namedWindow(result_window, CV_WINDOW_AUTOSIZE);

	/// ����������
	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);

	MatchingMethod(0, 0);

	waitKey(0);
	return 0;
}

/**
* @���� MatchingMethod
* @�򵥵Ļ������ص�����
*/
void MatchingMethod(int, void*)
{
	/// ������ʾ��ԭͼ��
	Mat img_display;
	img.copyTo(img_display);

	/// �����������ľ���
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create(result_cols, result_rows, CV_32FC1);

	/// ����ƥ��ͱ�׼��
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	/// ͨ������ minMaxLoc ��λ��ƥ���λ��
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// ���ڷ��� SQDIFF �� SQDIFF_NORMED, ԽС����ֵ������ߵ�ƥ����. ��������������, ��ֵԽ��ƥ��Խ��
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	/// ���ҿ����������ս��
	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, img_display);
	imshow(result_window, result);

	return;
}
#endif
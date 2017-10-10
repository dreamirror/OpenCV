#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp" 
#include<iostream>
#include<windows.h>  
#include <stdio.h>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
using namespace cv;
int g_nContrastValue;
int g_nBrightValue;
int g_SaveNum;
Mat g_srcImage, g_dstImage;
static void ContrasAndBright(int, void*);
static void SavePic(int, void*);

int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("read image err!");
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;
	namedWindow("效果窗口");
	createTrackbar("对比度:", "效果窗口", &g_nContrastValue, 300, ContrasAndBright);
	createTrackbar("亮度：", "效果窗口", &g_nBrightValue, 200, ContrasAndBright);
	createTrackbar("保存", "效果窗口", &g_SaveNum, 1, SavePic);
	ContrasAndBright(g_nContrastValue, 0);
	ContrasAndBright(g_nBrightValue, 0);

	while (char(waitKey(1)) != 'q')
	{
	
	}

	return 0;
}
static void SavePic(int, void*) {
	g_SaveNum = 0;
}

static void ContrasAndBright(int, void*) {
	namedWindow("【原始图窗口】", 1);

	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}

	imshow("【原始图窗口】", g_srcImage);
	imshow("【效果图窗口】", g_dstImage);
}

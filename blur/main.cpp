#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp" 
#include<iostream>
#include<windows.h>  
#include <stdio.h>
#include <math.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
using namespace cv;
int g_nContrastValue;
int g_nBrightValue;
int g_SaveNum;
Mat g_srcImage, g_dstImage;
static void ContrasAndBright(int, void*);
static void SavePic(int, void*);
void my_boxFilter(InputArray _src, OutputArray _dst, int ddepth, Size ksize);
int main() {
	//载入原图  
	Mat image = imread("lb.jpg");

	//创建窗口  
	namedWindow("均值滤波【原图】");
	namedWindow("均值滤波【效果图】");

	//显示原图  
	imshow("均值滤波【原图】", image);

	//进行滤波操作  
	Mat out;
	my_boxFilter(image, out, 0, Size(5, 5));

	//显示效果图  
	imshow("均值滤波【效果图】", out);

	waitKey(0);

	return 0;
}

void my_boxFilter(InputArray _src, OutputArray _dst, int ddepth, Size ksize) //方框均值滤波
{
	Mat src = _src.getMat();//原图的矩阵
	int sdepth = src.depth(),cn = src.channels();
	_dst.create(src.size(),CV_MAKETYPE(ddepth,cn)); //定义输出图像

	Mat dst = _dst.getMat();//输出图像的矩阵

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++){
		
			for (int c = 0; c < 3; c++)
			{
				double pix = 0.0;
				int pix_num = 0;
				int temp = ((x - floor(ksize.width / 2)) >= 0 ? (x - floor(ksize.width / 2)) : 0);
				//cout << temp << endl;
				for (int c_x = ((x - floor(ksize.width / 2)) >= 0 ? (x - floor(ksize.width / 2)) : 0); c_x <= ((x + ceil(ksize.width / 2)) < src.cols ? (x + ceil(ksize.width / 2)) : src.cols - 1); c_x++)
				{
					for (int c_y = ((y - floor(ksize.height / 2)) >= 0 ? (y - floor(ksize.height / 2)) : 0); c_y <= ((y + ceil(ksize.height / 2)) < src.rows ? (y + ceil(ksize.height / 2)) : src.rows - 1); c_y++) {
						pix += src.at<Vec3b>(c_y, c_x)[c];
						pix_num++;
					}
				}
				dst.at<Vec3b>(y, x)[c] = pix / pix_num;
				//cout << dst.at<Vec3b>(y, x)[c] << endl;
			}
		}
	}

}

//求每个通道的标准差




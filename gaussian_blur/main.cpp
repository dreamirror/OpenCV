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
void my_boxFilter(InputArray _src, OutputArray _dst, int ddepth, Size2d ksize);
Vec3f getSigma(int x , int y,Mat src, Size2d ksize);
double PI = 3.1415926;
int main() {
	//载入原图  
	Mat image = imread("lb.jpg");

	//创建窗口  
	namedWindow("高斯滤波【原图】");
	namedWindow("高斯滤波【效果图】");

	//显示原图  
	imshow("高斯滤波【原图】", image);

	//进行滤波操作  
	Mat out;
	my_boxFilter(image, out, 0, Size2d(5.0, 5.0));

	//显示效果图  
	imshow("高斯滤波【效果图】", out);

	waitKey(0);

	return 0;
}


//dst.at<Vec3b>(y, x)[c] = pix / pix_num;
void my_boxFilter(InputArray _src, OutputArray _dst, int ddepth, Size2d k_size) //方框均值滤波
{
	Mat src = _src.getMat();//原图的矩阵
	int sdepth = src.depth(),cn = src.channels();
	_dst.create(src.size(),CV_MAKETYPE(ddepth,cn)); //定义输出图像

	Mat dst = _dst.getMat();//输出图像的矩阵
	Size2d ksize = Size2d(k_size.width - 1, k_size.height - 1);
	
	ksize.width = ksize.width - 1;
	ksize.height = ksize.height - 1;
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++) {

			for (int c = 0; c < 3; c++)
			{
				double pix = 0.0;
				int pix_num = 0;
				Vec3f sigma = getSigma(x, y, src, ksize);
				double weight = 0.0;
				for (int c_x = ((x - floor(ksize.width / 2)) >= 0 ? (x - floor(ksize.width / 2)) : 0); c_x <= ((x + ceil(ksize.width / 2)) < src.cols ? (x + ceil(ksize.width / 2)) : src.cols - 1); c_x++)
					
				{
					for (int c_y = ((y - floor(ksize.height / 2)) >= 0 ? (y - floor(ksize.height / 2)) : 0); c_y <= ((y + ceil(ksize.height / 2)) < src.rows ? (y + ceil(ksize.height / 2)) : src.rows - 1); c_y++) {
						//double a = exp(-((x - c_x)*(x - c_x) + (y - c_y)*(y - c_y)) / 2 * sigma[c]) / (2 * PI * sigma[c]);
						//cout << "sigma[c]==" << sigma[c] << endl;
						//cout << "-( (x - c_x)*(x - c_x) +(y- c_y)*(y - c_y)) / 2 * sigma[c]==" << -((x - c_x)*(x - c_x) + (y - c_y)*(y - c_y)) / 2 * sigma[c] << endl;
						double f_x = x;
						double fc_x = c_x;
						double f_y = y;
						double fc_y = c_y;
						/*
						cout << "x = " <<x << endl;
						cout << "c_x = " << c_x << endl;
						cout << "y = " << y << endl;
						cout << "c_y = " << c_y << endl;
						cout << " -( (f_x - fc_x)*(f_x - fc_x) +(f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c]* sigma[c] ==" << -((f_x - fc_x)*(f_x - fc_x) + (f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c] * sigma[c] << endl;

						cout << " exp(-( (x - c_x)*(x - c_x) +(y- c_y)*(y - c_y)) / 2 * sigma[c]* sigma[c]) ==" << exp(-(((double)f_x - (double)fc_x)*((double)f_x - (double)fc_x) + ((double)f_y - (double)fc_y)*((double)f_y - (double)fc_y)) / 2 * sigma[c] * sigma[c]) << endl;
						cout << "权值==" << exp(-(((double)f_x - (double)fc_x)*((double)f_x - (double)fc_x) + ((double)f_y - (double)fc_y)*((double)f_y - (double)fc_y)) / 2 * sigma[c] * sigma[c]) / (2 * PI * sigma[c])<<endl;
						cout << "@@@@@" << endl;*/
						weight += exp(-((f_x - fc_x)*(f_x - fc_x) + (f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c] * sigma[c]) / (2 * PI * sigma[c]);

						dst.at<Vec3b>(y, x)[c] =  exp(-( (f_x - fc_x)*(f_x - fc_x) +(f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c]* sigma[c]) / (2 * PI * sigma[c]);
						
					}
				}

				for (int c_x = ((x - floor(ksize.width / 2)) >= 0 ? (x - floor(ksize.width / 2)) : 0); c_x <= ((x + ceil(ksize.width / 2)) < src.cols ? (x + ceil(ksize.width / 2)) : src.cols - 1); c_x++)

				{
					for (int c_y = ((y - floor(ksize.height / 2)) >= 0 ? (y - floor(ksize.height / 2)) : 0); c_y <= ((y + ceil(ksize.height / 2)) < src.rows ? (y + ceil(ksize.height / 2)) : src.rows - 1); c_y++) {
						double f_x = x;
						double fc_x = c_x;
						double f_y = y;
						double fc_y = c_y;
						weight += exp(-((f_x - fc_x)*(f_x - fc_x) + (f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c] * sigma[c]) / (2 * PI * sigma[c]);

						pix += src.at<Vec3b>(c_y, c_x)[c] * (exp(-((f_x - fc_x)*(f_x - fc_x) + (f_y - fc_y)*(f_y - fc_y)) / 2 * sigma[c] * sigma[c]) / (2 * PI * sigma[c]) / weight);

					}
				}
				dst.at<Vec3b>(y, x)[c] = pix;
				//cout << "--------------------------------" << endl;
				
			}
		}
	}
}

//求每个通道的标准差
Vec3f getSigma(int src_x,int src_y,Mat src, Size2d ksize) {

	Vec3f result = {};
	Vec3f mean = {};
	double n = 0;
	
	//期望值
	for (int c = 0; c < 3; c++)
	{
		n = 0;
		for (int c_x = ((src_x - floor(ksize.width / 2)) >= 0 ? (src_x - floor(ksize.width / 2)) : 0); c_x <= ((src_x + ceil(ksize.width / 2)) < src.cols ? (src_x + ceil(ksize.width / 2)) : src.cols - 1); c_x++)
		{
			for (int c_y = ((src_y - floor(ksize.height / 2)) >= 0 ? (src_y - floor(ksize.height / 2)) : 0); c_y <= ((src_y + ceil(ksize.height / 2)) < src.rows ? (src_y + ceil(ksize.height / 2)) : src.rows - 1); c_y++) {
				float temp = (float)src.at<Vec3b>(c_x, c_x)[c];
				float a = mean[c];
				//cout << temp << endl;
				//cout << a << endl;
				mean[c] +=(float) src.at<Vec3b>(c_x, c_x)[c];
				n++;
			}
		}
	//	cout << "----------------------------------" << endl;
		mean[c] = mean[c] / (n); 
		//cout << "mean[c]" << mean[c]<<endl;
	}
	//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	for (int c = 0; c < 3; c++)
	{
		for (int c_x = ((src_x - floor(ksize.width / 2)) >= 0 ? (src_x - floor(ksize.width / 2)) : 0); c_x <= ((src_x + ceil(ksize.width / 2)) < src.cols ? (src_x + ceil(ksize.width / 2)) : src.cols - 1); c_x++)

		{
			for (int c_y = ((src_y - floor(ksize.height / 2)) >= 0 ? (src_y - floor(ksize.height / 2)) : 0); c_y <= ((src_y + ceil(ksize.height / 2)) < src.rows ? (src_y + ceil(ksize.height / 2)) : src.rows - 1); c_y++) {
				float temp = ((float)src.at<Vec3b>(c_x, c_x)[c] - mean[c]);
				float a = mean[c];
			//	cout << temp << endl;
				//cout << a << endl;
				result[c] += temp * temp;
			}
		}
	//	cout << "result == " << result[c] << endl;
	//	cout << "----------------------------------" << endl;
		result[c] = result[c] / (n -1); //方差
	}
	return result;
}

double gaussian(double sigma,int x,int y) {
	double a = exp(-(x*x + y*y) / 2 * sigma) / (2 * PI * sigma);
}




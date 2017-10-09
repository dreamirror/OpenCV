#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
using namespace std;
using namespace cv;

bool MultiChannelBlending();

int main() {
	system("colorSE");
	if (MultiChannelBlending()) {
		cout << "success" << endl;
	}

	waitKey(0);

	return 0;
}

bool MultiChannelBlending(){
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat imageBlueChannel;

	logoImage = cv::imread("logo.jpg",0);
	srcImage = cv::imread("pic.jpg");
	if (logoImage.data == NULL) { printf("read logo err"); };
	if (srcImage.data == NULL) { printf("read src err"); };

	split(srcImage,channels);
	imageBlueChannel = channels.at(0);
	addWeighted(imageBlueChannel(Rect(50, 50, logoImage.cols, logoImage.rows)), 1.0, logoImage, 1, 0, imageBlueChannel(Rect(50, 50, logoImage.cols, logoImage.rows)));

	merge(channels,srcImage);
	namedWindow("原画加混合蓝色通道");
	imshow("原画加上logo的男色通道混合",srcImage);


	return true;
}


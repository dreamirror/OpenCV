
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>  
#include <stdio.h>
#include <io.h>
using namespace cv;
using namespace std;
Mat logo = imread("logo.png");

void out_logo(string bgname) {
	//载入图片  
	Mat image = imread("bg\\"+bgname);

	Mat imageROI;
	imageROI = image(Rect(50,50, logo.cols, logo.rows));
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	imwrite("output\\"+bgname, image);
	try {

	}
	catch (runtime_error& ex) {
		fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());
	}

}

int getfilename(void)
{
	_finddata_t fileDir;
	char* dir = "bg\\*.*";
	long lfDir;

	if ((lfDir = _findfirst(dir, &fileDir)) == -1l)
		printf("No file is found\n");
	else {
		printf("file list:\n");
		do {
			string name = (string)fileDir.name;
			int  leng = name.length();
			int dotpos = name.find(".");
			if (leng >= 4 && dotpos >= 0) {
				string suff = name.substr(dotpos, leng - 1);
				if (suff == ".png" || suff == ".jpg") {
					printf("%s\n", name);
					out_logo(name);
				}

			}


		} while (_findnext(lfDir, &fileDir) == 0);
	}
	_findclose(lfDir);

	return 0;
}

int main()
{
	//载入图片  
	getfilename();
	return 0;
	Mat image = imread("pic.jpg");
	Mat logo = imread("logo.png");

	
	//载入后先显示  
	namedWindow("【2】原画图");
	imshow("【2】原画图", image);

	namedWindow("【3】logo图");
	imshow("【3】logo图", logo);

	Mat imageROI;
	
	imageROI = image(Rect(50, 50, logo.cols, logo.rows));

	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	namedWindow("【4】原画+logo图");
	imshow("【4】原画+logo图", image);

	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	std::string str = "e:/";
	imwrite("1.jpg", image);
	try {
		
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());
		return 1;
	}




	waitKey();

		
	return 0;
}



#include <iostream>
#include <vector>
#include<stdlib.h>
#include <time.h> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "fstream"
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <direct.h> 
using namespace std;
using namespace cv;

extern int readDir(char *dirName, vector<string> &filesName);


int test47_ti(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	string stdpath = "E:/new_污损模糊 - 副本/统计污损/1";
	string imgpath = "E:/yu1-plate-data/4_正常车牌-制作污损";
	string savepath = "E:/yu1-plate-data/4_正常车牌-污损";

	vector<string> v_img_;
	readDir((char*)imgpath.c_str(), v_img_);
	
	vector<string> std_img_;
	readDir((char*)stdpath.c_str(), std_img_);

	for (int i = 0; i<v_img_.size(); i++)
	{
		string imagename = v_img_[i];

		//string imagename = "E:/yu1-plate-data/4_正常车牌-制作污损/132-苏E8H50L.jpg";

		int npos = imagename.find_last_of('/');
		int npos2 = imagename.find_last_of('.');

		string name1 = imagename.substr(npos + 1, npos2 - npos - 1);
		Mat src = imread(imagename.c_str());
		if (src.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		
		cout << imagename.c_str() << endl;


		for (int j = 0; j < std_img_.size();j++)
		{

			Mat img = src.clone();

			string stdname = std_img_[j];

			//string stdname ="E:/new_污损模糊 - 副本/统计污损/1/1.jpg";

			int npos = stdname.find_last_of('/');
			int npos2 = stdname.find_last_of('.');
			string name2 = stdname.substr(npos + 1, npos2 - npos - 1);

			Mat std = imread(stdname.c_str());
			if (std.data == NULL)
			{
				printf("std.data = NULL！\n");
				system("pause");
				continue;
			}

			cout << stdname.c_str() << endl;

			int  imgH = img.rows; int imgW = img.cols;
			int stdH = std.rows; int stdW = std.cols;
			
			if (imgH<stdH)
			{
				stdH = imgH-2;
			}

			if (imgW<stdW)
			{
				stdW = imgW - 2;
			}

			//cv::resize(std, std, Size(stdW, stdH));

			resize(std, std, Size(stdW, stdH));

			int x = 0; int y = 0;
			if (imgW - stdW - 1==0)
			{
				x = 0;
			}
			else
			{
				x = rand() % (imgW - stdW - 1);
			}
			
			if (imgH - stdH - 1==0)
			{
				y = 0;
			}
			else
			{
				y = rand() % (imgH - stdH - 1);
			}
	

			Mat roi = img(Rect(x,y,stdW,stdH));
			std.copyTo(roi);

			char file[1024];

			sprintf(file, "%s/%s-%s.jpg", savepath.c_str(),name1.c_str(),name2.c_str());
			imwrite(file,img);
		}
		

		



	}

	


	return 0;
}
int test47_get(int argc, char *argv[])
{

	
	

	


	




	return 0;
}
int test47(int argc, char *argv[])
{

	

	  test47_ti( argc, argv);

		//test47_get( argc, argv);


	return 0;
}



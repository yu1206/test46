#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "fstream"
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <direct.h> 
using namespace std;
using namespace cv;

extern int readDir(char *dirName, vector<string> &filesName);
struct imgfo
{
	string name;
	
	float perw;
	float perh;
};
//升序
bool LessSort3(imgfo a, imgfo b)
{
	float sidea = max(a.perw, a.perw);
	float sideb = max(b.perh, b.perh);
	return (sidea<sideb);
}

int test46(int argc, char *argv[])
{
	int stdlabel = 9;
	string imgpath = "E:/COCO/train2014/images";
	string savepath = "E:/COCO/train2014/traffic-light";
	mkdir(savepath.c_str());
	string wtxtpath = "E:/COCO/train2014/traffic-light/0_per.txt";
	string stxtpath = "G:/F/YOLO/darknet-master-yolov3/yolov3/get_coco_dataset/labels/train2014/";

	fstream finWrite;
	finWrite.open(wtxtpath, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string> v_img_; int num = 0;

	readDir((char*)imgpath.c_str(), v_img_);
	vector<imgfo> igf;
	int perminw = 10000; int perminh = 10000;
	int permaxw = 0; int permaxh = 0;

	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');

		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		cout << v_img_[i].c_str()<< endl;



		string str = stxtpath + "/" + name1 + ".txt";
		fstream finRead1;
		finRead1.open(str, ios::in);
		if (!finRead1.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			//system("pause");
			continue;
		}

		string line; int num1 = 0;

		while (getline(finRead1, line))
		{

			if (line.empty())
			{
				break;
			}

			num1++;

			int label; float cenx, ceny, cenw, cenh;
			stringstream str_s(line);
			str_s >> label >> cenx >> ceny >> cenw >> cenh;

			if (label==stdlabel)
			{
				Rect rt; 
				rt.x = (cenx - cenw/2)*img.cols;
				rt.y = (ceny-cenh/2)*img.rows;
				rt.width = cenw*img.cols;
				rt.height = cenh*img.rows;

				rectangle(img,rt,Scalar(0,0,255),2);

			
				  char c[8];
				  itoa(num1, c, 16);

				string str1 = savepath + "/" + name1+"_"+c + ".jpg";
				imwrite(str1.c_str(), img);

				imgfo igf1;
				igf1.name = name1;
				igf1.perw = cenw;
				igf1.perh = cenh;

				igf.push_back(igf1);


				if (cenw<perminw)
				{
					perminw = cenw;
				}
				if (cenh < perminh)
				{
					perminh = cenh;
				}

				if (cenw>permaxw)
				{
					permaxw = cenw;
				}
				if (cenh > permaxh)
				{
					permaxh = cenh;
				}
			}
			


		}

		finRead1.close();

		

	}
	
	printf("perminw=%f,perminh=%f,permaxw=%f,permaxh=%f\n", perminw, perminh, permaxw, permaxh);

	sort(igf.begin(), igf.end(), LessSort3);//升序排列

	for (int j = 0; j < igf.size(); j++)
	{
		imgfo vi = igf[j];
		finWrite << vi.name << " " << vi.perw << " " << vi.perh <<endl;
	}

	finWrite.close();
	

	return 0;
}



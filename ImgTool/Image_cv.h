#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;
using namespace cv;
#pragma once
class CImage_cv
{
public:
	CImage_cv(void);
	~CImage_cv(void);
	void readImage(const string& name) ;
	void showImage();
	int saveImage();
	Mat& getImg(void){return m_Image;};
private:
	Mat m_Image;
	string m_Imagename;
	bool m_iReady;
};


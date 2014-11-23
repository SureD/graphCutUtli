#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "string"
#include <vector>
extern "C" {
#include "vl/generic.h"
#include "vl/slic.h"
}
#pragma once
using namespace std;
using namespace cv;
class CSlic
{
public:
	CSlic(Mat& image ,int region,float regularization,int minRegion);
	~CSlic(void);


	// return labels of the segmentation, which saved as the same size of the
	// input image with only one channle;
	vector<int>& getLabels();  
					  
	void doSlicSegmentation();
	void showSlicResult();
private:
	//methods
	void convertResultToVector();
	bool initImgArray();
	// OpenCV data structure
	Mat m_slicMat;
	vector<int> m_labels;
	// vlfeat  data structure
	vl_uint32* m_segmentationArray;  // one-dimensional array
	vl_size m_height ;
	vl_size m_width ;
	vl_size m_channel;
	float* m_imageArray;
	// The region size defines the number of superpixels obtained.
	// Regularization describes a trade-off between the color term and the
	// spatial term.
	// The param should be provide by user
	vl_size m_region;        
	float m_regularization;
	vl_size m_minRegion;
};


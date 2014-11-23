#include "Slic.h"


CSlic::CSlic(Mat &image,int region,float regularization,int minRegion):
	m_slicMat(image),  //initialize
	m_region(region),
	m_regularization(regularization),
	m_minRegion(minRegion)
{
	CV_Assert(!m_slicMat.empty());
	m_height = m_slicMat.rows;
	m_width = m_slicMat.cols;
	m_channel = m_slicMat.channels();
	m_segmentationArray = new vl_uint32[m_width*m_height];
	m_imageArray = new float[m_width*m_height*m_channel];
	if(NULL == m_segmentationArray||NULL == m_imageArray){
		std::cout<<"out of memory!"<<std::endl;
		assert(0);
	}
	
}


CSlic::~CSlic(void)
{
	delete[] m_segmentationArray;
	delete[] m_imageArray;
}

bool CSlic::initImgArray()
{
	if(NULL==m_imageArray){
		return 0;
	}else{
			for (int i = 0; i < m_slicMat.rows; ++i) {
				for (int j = 0; j < m_slicMat.cols; ++j) {
					// Assuming three channels ...
					m_imageArray[j + m_slicMat.cols*i + m_slicMat.cols*m_slicMat.rows*0] = m_slicMat.at<cv::Vec3b>(i, j)[0];
					m_imageArray[j + m_slicMat.cols*i + m_slicMat.cols*m_slicMat.rows*1] = m_slicMat.at<cv::Vec3b>(i, j)[1];
					m_imageArray[j + m_slicMat.cols*i + m_slicMat.cols*m_slicMat.rows*2] = m_slicMat.at<cv::Vec3b>(i, j)[2];
				}
			}
	}
	return 1;
}
void CSlic::doSlicSegmentation()
{
	if(initImgArray())
	{
		vl_slic_segment(m_segmentationArray, m_imageArray, 
						m_width, m_height, m_channel,
						m_region, m_regularization, m_minRegion);
	}
}
void CSlic::convertResultToVector()
{
	int sz = m_slicMat.rows*m_slicMat.cols;
	for(int i=0;i<sz;++i){
		m_labels.push_back((int)m_segmentationArray[i]);
	}

}
vector<int>& CSlic::getLabels()
{
	convertResultToVector();
	return m_labels;
}
void CSlic::showSlicResult()
{
	Mat t_Mat;
	m_slicMat.copyTo(t_Mat);
	int** labels = new int*[m_slicMat.rows];
	for (int i = 0; i < m_slicMat.rows; ++i) {
		labels[i] = new int[m_slicMat.cols];

		for (int j = 0; j < m_slicMat.cols; ++j) {
			labels[i][j] = (int) m_segmentationArray[j + m_slicMat.cols*i];
		}
	}

	int label = 0;
	int labelTop = -1;
	int labelBottom = -1;
	int labelLeft = -1;
	int labelRight = -1;

	for (int i = 0; i < m_slicMat.rows; i++) {
		for (int j = 0; j < m_slicMat.cols; j++) {

			label = labels[i][j];

			labelTop = label;
			if (i > 0) {
				labelTop = labels[i - 1][j];
			}

			labelBottom = label;
			if (i < m_slicMat.rows - 1) {
				labelBottom = labels[i + 1][j];
			}

			labelLeft = label;
			if (j > 0) {
				labelLeft = labels[i][j - 1];
			}

			labelRight = label;
			if (j < m_slicMat.cols - 1) {
				labelRight = labels[i][j + 1];
			}

			if (label != labelTop || label != labelBottom || label!= labelLeft || label != labelRight) {
				t_Mat.at<cv::Vec3b>(i, j)[0] = 0;
				t_Mat.at<cv::Vec3b>(i, j)[1] = 0;
				t_Mat.at<cv::Vec3b>(i, j)[2] = 255;
			}
		}
	}
	const string winName = "SLIC Result";
	cv::namedWindow( winName, WINDOW_AUTOSIZE );
	cv::imshow(winName, t_Mat);
	cv::waitKey();
	for (int i = 0; i < t_Mat.rows; ++i) {
		delete[] labels[i];
	}
	delete[] labels;
}
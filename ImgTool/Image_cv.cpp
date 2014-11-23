#include "Image_cv.h"


CImage_cv::CImage_cv(void):
m_iReady(0)
{
	//m_Image = nullptr;
}


CImage_cv::~CImage_cv(void)
{

}
void CImage_cv::readImage(const string& name){
	//m_Imagename=name;
	m_Imagename = name;
	try{
	m_Image = imread(m_Imagename,CV_LOAD_IMAGE_COLOR);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception loading image: %s\n", ex.what());
	}
	m_iReady = true;
}
void CImage_cv::showImage(){
	if(m_iReady){
		const string winName = (m_Imagename+" Show");
		namedWindow( winName, WINDOW_AUTOSIZE );
		cout<<"PRESS ANY KEY TO CONTINUE "<<endl;
		imshow(winName,m_Image);
		waitKey(0);
		
	}
}
int CImage_cv::saveImage(){
		const string filename = ("./output/"+m_Imagename);
		try {
			imwrite(filename, m_Image);
		}
		catch (runtime_error& ex) {
			fprintf(stderr, "Exception storing image: %s\n", ex.what());
			return 0;
		}
		return 1;


}

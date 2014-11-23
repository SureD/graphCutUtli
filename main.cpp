// OpenCV can be used to read images.
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "GrabCut/grabCutTool.h"
#include "Slic/Slic.h"
// The VLFeat header files need to be declared external.
#include <iostream>
using namespace std;
using namespace cv;
#include "ImgTool/Image_cv.h"
static void help()
{
	cout << "\nThis program demonstrates GrabCut segmentation -- select an object in a region\n"
		"and then grabcut will attempt to segment it out.\n"
		"Call:\n"
		"./grabcut <image_name>\n"
		"\nSelect a rectangular area around the object you want to segment\n" <<
		"\nHot keys: \n"
		"\tESC - quit the program\n"
		"\tr - restore the original image\n"
		"\tn - next iteration\n"
		"\n"
		"\tleft mouse button - set rectangle\n"
		"\n"
		"\tCTRL+left mouse button - set GC_BGD pixels\n"
		"\tSHIFT+left mouse button - set CG_FGD pixels\n"
		"\n"
		"\tCTRL+right mouse button - set GC_PR_BGD pixels\n"
		"\tSHIFT+right mouse button - set CG_PR_FGD pixels\n"
        "\n"
        "\ts- use slic segmentation\n "<< endl;
}
GCApplication gcapp;

static void on_mouse( int event, int x, int y, int flags, void* param )
{
	gcapp.mouseClick( event, x, y, flags, param );
}
int main( int argc, char** argv )
{
    	if( argc!=2 )
    	{
        	help();
       		return 1;
    	}
    	string filename = argv[1];

	// Read the Lenna image. The matrix 'mat' will have 3 8 bit channels
	// corresponding to BGR color space.

// 	const string imagename = "I:\\CodeZone\\test\\3096.jpg";
// 	cv::Mat mat = cv::imread(imagename, CV_LOAD_IMAGE_COLOR);
// 	////////////test//////////
// 	GCGraph<int> T;
// 	CImage_cv testcv;
// 	testcv.readImage(imagename);
// 	testcv.showImage();
// 	CSlic tests(mat,40,1000,10);
// 	tests.doSlicSegmentation();
// 	tests.showSlicResult();
//	string filename = "lena.jpg";
	if( filename.empty() )
	{
		cout << "\nDurn, couldn't read in " <<filename << endl;
		return 1;
	}
	Mat image = imread( filename, 1 );
	if( image.empty() )
	{
		cout << "\n Durn, couldn't read image filename " << filename << endl;
		return 1;
	}

	help();
    /// SLIC Test
    // 
    Mat image2;
    image2 = image.clone();
    CSlic slictest(image2,40,1000,10);
    cout<<"This is SLic Algorithm\n"
    "When you see the result of the Slic, Please press any key to continue\n"<<endl;
    slictest.doSlicSegmentation();
    slictest.showSlicResult();
    //
    // Grab
	const string winName = "image";
	namedWindow( winName, WINDOW_AUTOSIZE );
	setMouseCallback( winName, on_mouse, 0 );
	gcapp.setImageAndWinName( image, winName );
	gcapp.showImage();
	for(;;)
	{
		int c = waitKey(0);
		switch( (char) c )
		{
		case '\x1b':
			cout << "Exiting ..." << endl;
			goto exit_main;
		case 'r':
			cout << endl;
			gcapp.reset();
			gcapp.showImage();
			break;
		case 'n':
			int iterCount = gcapp.getIterCount();
			cout << "<" << iterCount << "... ";
			int newIterCount = gcapp.nextIter();
			if( newIterCount > iterCount )
			{
				gcapp.showImage();
				cout << iterCount << ">" << endl;
			}
			else
				cout << "rect must be determined>" << endl;
			break;
		}
	}

exit_main:
	destroyWindow( winName );
 	return 0;

}

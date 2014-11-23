#include <opencv2/opencv.hpp>
#include "GCGraph.h"
#include "GMM.hpp"
#include <vector>
using namespace std;
using namespace cv;
//! class of the pixel in GrabCut algorithm

class grabCutT
{
public:
	grabCutT(void);
	~grabCutT(void);
	void grab_Cut( Mat _img, Mat& _mask, Rect& rect,
		Mat &_bgdModel, Mat& _fgdModel,
		int iterCount, int mode  );
private:
	double calcBeta( const Mat& img );
	void calcNWeights( const Mat& img, Mat& leftW, Mat& upleftW, Mat& upW, Mat& uprightW, double beta, double gamma );
	void checkMask( const Mat& img, const Mat& mask );
	void initMaskWithRect( Mat& mask, Size imgSize, Rect rect );
	void initGMMs( const Mat& img, const Mat& mask, GMM& bgdGMM, GMM& fgdGMM );
	void assignGMMsComponents( const Mat& img, const Mat& mask, const GMM& bgdGMM, const GMM& fgdGMM, Mat& compIdxs );
	void learnGMMs( const Mat& img, const Mat& mask, const Mat& compIdxs, GMM& bgdGMM, GMM& fgdGMM );
	void constructGCGraph( const Mat& img, const Mat& mask, const GMM& bgdGMM, const GMM& fgdGMM, double lambda,
		const Mat& leftW, const Mat& upleftW, const Mat& upW, const Mat& uprightW,
		GCGraph<double>& graph );
	void estimateSegmentation( GCGraph<double>& graph, Mat& mask );


};

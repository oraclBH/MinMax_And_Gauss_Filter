#include "arith.h"

int main()
{
#if 0
	Mat I = imread("..\\Thoracic-2.png", 1);    
	namedWindow("src_image", CV_WINDOW_NORMAL);
	imshow("src_image", I);
#else
	Mat I = imread("..p\\SPYOverlay.png", 1);
	namedWindow("src_image", CV_WINDOW_NORMAL);
	imshow("src_image", I);
#endif


#if 1
	int win = 1;
#else
	int win = 2;
#endif

 
	minMaxfilter  a(win);
	Mat d;
	a.execute(I, d);
	namedWindow("minMax_image", CV_WINDOW_NORMAL);
	imshow("minMax_image", d);


	int gass_win = 7;
	float gass_delt = 10.0f;
	Mat g;
	gaussFilter b(gass_win, gass_delt);
	b.execute(I, g);
	namedWindow("gauss_image", CV_WINDOW_NORMAL);
	imshow("gauss_image", g);


	waitKey(0);
	return 0;
}
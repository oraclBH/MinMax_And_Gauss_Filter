#pragma once
#ifndef ARITH_H

#include "arith.h"

#include <AccCtrl.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;


#define  PI  3.14

class minMaxfilter
{
public:
	minMaxfilter(int win);
	~minMaxfilter();
	uchar convert_double2uchar(double src);
	void execute(const Mat& src, Mat& dst);

private:
	int winsize;
};

class gaussFilter
{
public:
	gaussFilter(int win, float delt);
	~gaussFilter();
	uchar convert_float2uchar(float src);
	void execute(const Mat& src, Mat& dst);

private:
	int		winsize;
	float	gdelt;
	float*  kernel;
	void generateGaussKernel();
};



#endif

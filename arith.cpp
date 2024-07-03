#include "arith.h"


minMaxfilter::minMaxfilter(int win)
{
	winsize = win;
}

minMaxfilter::~minMaxfilter()
{
	cout << "Min Max filtering \n" << endl;
}

uchar gaussFilter::convert_float2uchar(float  src)
{
	uchar dst;
	if (src < 0.5f)
	{
		dst = 0;
	}
	else if (src > 254.5f)
	{
		dst = 255;
	}
	else
	{
		dst = (unsigned char)src;
	}

	return dst;
}

uchar minMaxfilter::convert_double2uchar(double src)
{
	uchar dst;
	if (src < 0.5f)
	{
		dst = 0;
	}
	else if (src > 254.5f)
	{
		dst = 255;
	}
	else
	{
		dst = (unsigned char)src;
	}

	return dst;
}


void minMaxfilter::execute(const Mat& src, Mat& dst)
{
	double minvalue, maxvalue;
	
	Mat gray_img, block;
	cvtColor(src, gray_img, CV_RGB2GRAY);
    dst = gray_img.clone();
	int high, wight;
	high = gray_img.rows;
	wight = gray_img.cols;
	int win = winsize;

	for (int y = win; y < high-win; y++)
	{
		for (int x = win; x < wight-win; x++)
		{
			try
			{
				block = gray_img(Rect(x-win, y-win, 2 * win + 1, 2 * win + 1));
				minMaxLoc(block, &minvalue, &maxvalue);
				dst.at<uchar>(y, x) = convert_double2uchar(maxvalue - minvalue);
			}
			catch (...)
			{
				int curx = x;
				int cury = y;
			}
		}
	}
}

gaussFilter::gaussFilter(int win, float delt)
{
	winsize = win;
	gdelt = delt;
}

gaussFilter::~gaussFilter()
{
	delete[] kernel;
	cout << "Gauss Filter is doing...\n" << endl;
}

void gaussFilter::generateGaussKernel()
{
	kernel = new float[(2*winsize+1)*(2 * winsize + 1)];
	int win = winsize;
	float delt = gdelt;
	int k = 0;
	float sumv = 0.0f;
	int num = (2 * win + 1) * (2 * win + 1);

	for (int y = -win; y < win; y++)
	{
		for (int x = -win; x < win; x++)
		{
			kernel[k] =  1.0f / (2 * PI * delt * delt) * exp(-(x ^ 2 + x ^ 2) / 2 / delt / delt);
			sumv += kernel[k];
			k++;
		}
	}

	for (int index = 0; index < num; index++)
	{
		kernel[index] /= sumv;
	}
}

void gaussFilter::execute(const Mat& src, Mat& dst)
{
	generateGaussKernel();

	int high = src.rows;
	int wight = src.cols;
	int channel = src.channels();
	dst = Mat::zeros(high, wight, src.type());
	
	Mat tmprow = Mat::zeros(high, wight + 2 * winsize, src.type());
	for (int i = 0; i < tmprow.rows; i++)
	{
		for (int j = 0; j < tmprow.cols; j++)
		{
			if (i>=winsize && i <tmprow.rows - winsize && j >= winsize && j < tmprow.cols - winsize)
			{
				tmprow.at<Vec3b>(i, j) = src.at<Vec3b>(i - winsize, j - winsize);
			}
		}
	}

	Mat tmp = Mat::zeros(high + 2 * winsize, wight + 2 * winsize, src.type());
	memcpy(tmp.data + winsize*(wight + 2 * winsize)*channel, tmprow.data, high*(wight + 2 * winsize)*channel);

	
	for (int c = 0; c < channel; c++)
	{
		for (int y = winsize; y < tmp.rows - winsize; y++)
		{
			for (int x = winsize; x < tmp.cols - winsize; x++)
			{
				int k = 0;
				float sumv  = 0.0f;
				try
				{
					for (int indey = y - winsize; indey < y + winsize; indey++)
					{
						for (int index = x - winsize; index < x + winsize; index++)
						{
							sumv += kernel[k++] * tmp.at<Vec3b>(indey, index)[c];
						}
					}

					dst.at<Vec3b>(y-winsize, x-winsize)[c] = convert_float2uchar(sumv);
				}
				catch (...)
				{
					int indexc = c;
					int indexy = y;
					int indexx = x;
				}
			}
		}
	}
}
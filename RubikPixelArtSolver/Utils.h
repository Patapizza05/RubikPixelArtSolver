#ifndef UTILS_HEADER
#define UTILS_HEADER	

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "RubikColor.h"

using cv::Scalar;
using cv::String;
using cv::Rect;
using cv::VideoCapture;
using cv::Mat;
using cv::Vec4i;

struct SquareRubik{
	cv::Point2f position;
	RubikColor color;

	SquareRubik(cv::Point2f point, RubikColor col) : position(point), color(col) {}
};

#endif
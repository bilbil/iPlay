#ifndef IMAGEUTILITY_H
#define IMAGEUTILITY_H

#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

using namespace cv;

Mat OpenImageMat(string filepath);

Mat ConvertUcharRgbToMat(unsigned char * in, int width, int height);

#endif

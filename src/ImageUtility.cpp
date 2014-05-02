#include "ImageUtility.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat OpenImageMat(string filepath)
{
  Mat image;

  image = imread(filepath.c_str(), CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data )                              // Check for invalid input
  {
    cout <<  "Could not open or find the image" << std::endl;
  }

  return image;
}

Mat ConvertUcharRgbToMat(unsigned char * in, int width, int height)
{
  //create new mat
  Mat image = cv::Mat(height, width, CV_8UC3);
 
  Size imgSize = image.size();

  for (int row=0;row<imgSize.height;row++) {
    unsigned char *data = image.ptr(row);
    for (int col=0;col<imgSize.width;col++) {
      //blue
      *data = *(in+2); 
      //green
      *(data+1) = *(in+1);
      //red
      *(data+2) = *in;
      
      //increment
      data+=3;
      in+=3;
    }
  }

  return image;
}

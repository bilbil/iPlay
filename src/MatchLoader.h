#ifndef MATCHLOADER_H
#define MATCHLOADER_H

#include <map>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

using namespace cv;
using namespace std;

/// template match image manager provides ability to add and retrieve template images
class MatchLoader
{
 public:
  MatchLoader();

  /// stores template images
  map<string, vector<Mat> > mMatch;

  /// adds a new template image
  void AddMatch(string id, string filepath);
  
  /// finds the template image
  vector<Mat> GetMatchImage(string id);

  /// gets the best match
  bool GetBestMatch(Mat input, Rect roi, string id, Mat& output, int& matchFactor, int& x, int& y);
  
};

#endif

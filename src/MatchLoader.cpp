#include "MatchLoader.h"
#include "ImageUtility.h"

#include <map>
#include <string>
#include <vector>
#include <tuple>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

using namespace std;
using namespace cv;

MatchLoader::MatchLoader()
{
}

void MatchLoader::AddMatch(string id, string path)
{

  //open file
  Mat image = OpenImageMat(path);
  if(! image.data )                              // Check for invalid input
  {
    cout <<  "Could not open or find the image: "<< path <<endl;
    return;
  }

  auto it = this->mMatch.find(id);

  if(it == this->mMatch.end()){
    vector<Mat> newVec;
    this->mMatch.insert(std::pair<string,vector<Mat> >(id,newVec));  // max effi
    it = this->mMatch.find(id);
  }

  //add to map
  it->second.push_back(image);
}

vector<Mat> MatchLoader::GetMatchImage(string id)
{
  vector<Mat> images;
  map<string,vector<Mat> >::iterator it;
  it = this->mMatch.find(id);

  if(it == mMatch.end())
    return images;

  images = it->second;

  // for(auto i : images){
  //   imshow("Template", i);   
  //   waitKey(0);         
  // }

  return images;
}

bool MatchLoader::GetBestMatch(Mat input, Rect roi, string id, Mat& output, int& matchFactor, int& x, int& y)
{
  // typedef tuple<int,int,int, Mat> matchdata; //stores coeff, x, y, output of matched result
  // vector<matchdata> matchresults;

  //get the vector of template images for matching
  vector<Mat> templates = GetMatchImage(id);

  // for(auto i : templates){
  //   imshow("Template", i);   
  //   waitKey(0);         
  // }

  Rect roiCopy = roi;

  if(templates.empty())
    return false;

  bool firstpass = true;

  for(auto i : templates)
  {
    Mat templateImage = i;

    //cross correlation test 
    Mat result;

    roiCopy.width = roi.width - templateImage.cols;
    roiCopy.height = roi.height - templateImage.rows;
   
    //match it!
    matchTemplate(input, templateImage, result, CV_TM_CCOEFF);

    //filter to roi region only
    Mat resultFiltered = Mat(result.size(), result.type(), 0.0);
    result(roiCopy).copyTo(resultFiltered(roiCopy));

    // imshow( "result filtered", resultFiltered); 
    // waitKey(0);
    
    //get max of match
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc(resultFiltered, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    
    //save result for each template
    // matchdata _matchdata = make_tuple(maxVal, maxLoc.x + templateImage.cols/2, maxLoc.y + templateImage.rows/2, resultFiltered);
    // matchresults.push_back(_matchdata);

    if(firstpass == true){
      x = maxLoc.x + templateImage.cols/2;
      y = maxLoc.y + templateImage.rows/2;
      matchFactor = maxVal;
      output = resultFiltered;
    }
    else{
      if(maxVal > matchFactor){
	x = maxLoc.x + templateImage.cols/2;
	y = maxLoc.y + templateImage.rows/2;
	matchFactor = maxVal;
	output = resultFiltered;
      }
    }
  }

  //normalize matching image
  normalize( output, output, 0, 1, NORM_MINMAX, -1, Mat() );

  return true;
}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

#include <iostream>
#include <unistd.h>

#include "ImageUtility.h"
#include "Capture.h"
#include "MatchLoader.h"
#include "WindowUtility.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  if(argc < 7)
  {
      cout<<"args: displayX, displayY, offx, offy, sizex, sizey"<<endl;
      return -1;
  }

  int DisplaySizeX = atoi(argv[1]);
  int DisplaySizeY = atoi(argv[2]);
  int offsetx = atoi(argv[3]);
  int offsety = atoi(argv[4]);
  int sizex = atoi(argv[5]);
  int sizey = atoi(argv[6]);

  namedWindow( "Capture", WINDOW_AUTOSIZE );// Create a window for display.
  // namedWindow( "Template", WINDOW_AUTOSIZE );// Create a window for display.
  // namedWindow( "Best Match", WINDOW_AUTOSIZE );// Create a window for display.

  //load template images
  MatchLoader _MatchLoader;

  _MatchLoader.AddMatch("cow", "../testcase/pics/cow1.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow2.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow3.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow4.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow5.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow6.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow7.jpg");
  _MatchLoader.AddMatch("cow", "../testcase/pics/cow8.jpg");

  while(true)
  {
    //capture screen area and store in pImage
    unsigned char * pImage;
    int ret = GetFrame(DisplaySizeX, DisplaySizeY, offsetx, offsety, sizex, sizey, pImage);
    if(ret != 0)
      cout<<"error"<<endl;

    //convert screen capture to opencv mat
    Mat capture = ConvertUcharRgbToMat(pImage, sizex, sizey);

    //best match result
    Mat bestMatchImg;
    int matchFactor;
    int matchx;
    int matchy;

    //mask to only the play area
    Rect roi(25,5,518,335);

    // Mat playArea = Mat(capture.size(), CV_32FC3);
    // capture(roi).copyTo(playArea(roi));

    bool isMatched = _MatchLoader.GetBestMatch(capture, roi, "cow", bestMatchImg, matchFactor, matchx, matchy);

    if(isMatched == false)
      continue;

    Point center;
    center.x = matchx;
    center.y = matchy;

    circle(capture, center,2,Scalar(1,1,0),CV_FILLED, 8,0);
    
    cout<<"best match coefficient: "<<matchFactor<<", position: "<<matchx<<", "<<matchy<<endl;
    
    //draw playarea border
    Point pt1(25, 5);
    Point pt2(518 + 25,335 + 5);
    rectangle(capture, pt1, pt2, Scalar(1,1,1), 1, 8, 0);

    imshow("Capture", capture);    
    imshow( "Best Match", bestMatchImg); 

    MouseMove(matchx+52, matchy+52, 3);
    
    waitKey(0);         
  }

  cout<<"round done"<<endl;

  waitKey(0);   

  return 0;
}

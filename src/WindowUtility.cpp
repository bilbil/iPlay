#include "WindowUtility.h"
#include "Interpolate.h"

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <unistd.h>

using namespace std;

void MouseMove(int x, int y, int steps)
{
  //using Xautomation or Xdotool utlity
  string xtool = "xdotool ";
  string command = "mousemove ";
  string call ="";

  //use linear interpolation for moving
  float mousePosOld[2];
  float mousePosNew[2];
  mousePosNew[0] = x;
  mousePosNew[1] = y;
  float mousePosCur[2];
  int mouseDim = 2;
  int mouseStep = steps;
  bool mouseDone = false;

  Interpolate Iterpolate;
  
  //get current mouse position
  FILE *lsofFile_p = popen("xdotool getmouselocation", "r");
  if (!lsofFile_p)
  {
    return;
  }
  char buffer[1024];
  char *line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
  pclose(lsofFile_p);
  stringstream ss0;

  string strPos(buffer);
  ss0 << strPos<<endl;
  string strposx, strposy;
  ss0 >> strposx;
  ss0 >> strposy;
  
  mousePosOld[0] = atoi(strposx.substr(2).c_str());
  mousePosOld[1] = atoi(strposy.substr(2).c_str());

  cout<<mousePosOld[0]<<endl;
  cout<<mousePosOld[1]<<endl;

  while(mouseDone == false){
    Iterpolate.InterpolateLinear(mouseDim, mousePosOld, mousePosNew, mouseStep, mousePosCur, mouseDone);   

    stringstream ss;

    for(int i = 0; i < mouseDim; i++){
      ss << (int)mousePosCur[i] <<" ";
    }

    call = xtool + command + ss.str();
    cout<<"called: "<<call<<endl;
    system(call.c_str());

    // usleep(5);
  }
}

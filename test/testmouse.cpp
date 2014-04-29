#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "interpolate.h"

using namespace std;

int main(int argc,char * argv[]) {

  //using Xautomation or Xdotool utlity
  string xtool = "xdotool ";
  string command = "mousemove ";
  string call ="";

  //use linear interpolation for moving
  int mousePosOld[2] = {0,0};
  int mousePosNew[2] = {500,500};
  int mousePosCur[2] = {0,0};
  int mouseDim = 2;
  int mouseStep = 500;
  bool mouseDone = false;

  interpolate Iterpolate;
  
  while(mouseDone == false){
    Iterpolate.interpolateLinear(mouseDim, mousePosOld, mousePosNew, mouseStep, mousePosCur, mouseDone);   

    stringstream ss;

    for(int i = 0; i < mouseDim; i++){
      ss << mousePosCur[i] <<" ";
    }

    call = xtool + command + ss.str();
    cout<<"called: "<<call<<endl;
    system(call.c_str());
    usleep(30);
  }

  return 0;
}

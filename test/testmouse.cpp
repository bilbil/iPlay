#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <unistd.h>

#include "Interpolate.h"
#include "WindowUtility.h"

using namespace std;

int main(int argc,char * argv[]) {

  //using Xautomation or Xdotool utlity
  string xtool = "xdotool ";
  string command = "mousemove ";
  string call ="";

  //use linear interpolation for moving
  float mousePosNew[2] = {500,500};
  int mouseStep = 50;

  MouseMove(mousePosNew[0], mousePosNew[1], mouseStep);

  return 0;
}

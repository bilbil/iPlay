#include <iostream>
#include <string>

#include "capture.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 8)
  {
      cout<<"args: displayX, displayY, offx, offy, sizex, sizey, outputpath"<<endl;
      return -1;
  }

  int DisplaySizeX = atoi(argv[1]);
  int DisplaySizeY = atoi(argv[2]);
  int offsetx = atoi(argv[3]);
  int offsety = atoi(argv[4]);
  int sizex = atoi(argv[5]);
  int sizey = atoi(argv[6]);
  string outputpath = string(argv[7]);

  cout<<outputpath<<endl;
  
  unsigned char * pImage;
  int ret = GetFrame(DisplaySizeX, DisplaySizeY, offsetx, offsety, sizex, sizey, pImage);
  if(ret != 0)
    cout<<"error"<<endl;

  SaveFrame(pImage, sizex, sizey, outputpath);

  return 0;
}

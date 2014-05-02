#ifndef CAPTURE_H
#define CAPTURE_H

#include<string>

#ifdef __cplusplus
extern "C" {
#endif
  
#include<libavcodec/avcodec.h>
#include<libswscale/swscale.h>
#include<libavformat/avformat.h>
#include<libavdevice/avdevice.h>
#include<libavfilter/avfilter.h>

#ifdef __cplusplus
}
#endif

using namespace std;

///saves picture
void SaveFrame(unsigned char * img, int width, int height, string outputpath);

///grabs the window pciture
int GetFrame(int DisplaySizeX, int DisplaySizeY, int offsetx, int offsety, int sizex, int sizey, unsigned char*& rgb);

///convert to rgb with crop offset and crop size
void ConvertToRGB(AVFrame *pFrame, unsigned char*& rgb, int offsetx, int offsety, int width, int height);

#endif

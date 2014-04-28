 #include<iostream>
 #include<stdio.h>
 #include<assert.h>
 #include<fstream>

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

int main(int argc, char *argv[]) {
  // register devices, filters and codecs
  av_register_all();

  std::cout<<"exited"<<std::endl;

  return 0;
}

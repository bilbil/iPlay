#include<iostream>
#include<stdio.h>
#include<assert.h>
#include<fstream>
#include<string>

#include <sstream>

#include "capture.h"

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

void SaveFrame(unsigned char* rgb, int width, int height, string outputfile)
{
  FILE *pFile;
  char szFilename[32];
  int y;

  string out = outputfile;
  out = out + ".ppm";
  pFile = fopen(out.c_str(), "wb");
  if (pFile == NULL)
    return;

  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
  fwrite(rgb, 3, width * height, pFile);

  // Close file
  fclose(pFile);
}

int GetFrame(int DisplaySizeX, int DisplaySizeY, int offsetx, int offsety, int crop_w, int crop_h, unsigned char*& rgb)
{

  AVFormatContext *pFormatCtx = NULL;
  int i, videoStream;
  AVCodecContext *pCodecCtx;
  AVCodec *pCodec;
  AVFrame *pFrame;
  AVFrame *pFrameCropped;
  AVFrame *pFrameRGB;
  struct SwsContext * pSwsCtx;
  AVPacket packet;
  int frameFinished;
  int numBytes;
  int numBytesCroped;
  uint8_t *buffer;
  uint8_t *bufferCroped;
  
    AVDictionary * p_options = NULL;
    AVInputFormat * p_in_fmt = NULL;

    // Register all formats and codecs
    av_register_all();
    avcodec_register_all();
    avdevice_register_all();

    stringstream ss;
    ss << DisplaySizeX <<"x"<<DisplaySizeY;
    string DisplaySize = ss.str();
    cout<<DisplaySize<<endl;

    av_dict_set(&p_options, "framerate", "25", 0);
    av_dict_set(&p_options, "video_size", DisplaySize.c_str(), 0);
    p_in_fmt = av_find_input_format("x11grab");

    // Open video file
    if (avformat_open_input(&pFormatCtx, ":0.0",
                            p_in_fmt, &p_options) != 0)
    {
        printf("cannot open input file!\n");
        return -1; // Couldn't open file
    }

    // Retrieve stream information
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return -1; // Couldn't find stream information

    // Dump information about file onto standard error
    char fileinfo[6000];
    av_dump_format(pFormatCtx, 0, fileinfo, 0);
    cout<<fileinfo<<endl;

    // Find the first video stream
    videoStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    if (pFormatCtx->streams[i]->codec->codec_type 
                                == AVMEDIA_TYPE_VIDEO)
    {
        videoStream = i;
        break;
    }
    if (videoStream == -1)
        return -1; // Didn't find a video stream

    // Get a pointer to the codec context for the video stream
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    // Find the decoder for the video stream
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        fprintf(stderr, "Unsupported codec!\n");
        return -1; // Codec not found
    }
    // Open codec
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
        return -1; // Could not open codec

    // Allocate video frame
    pFrame = avcodec_alloc_frame();

    int crop_x = offsetx;
    int crop_y = offsety;

    pFrameCropped = avcodec_alloc_frame();

    if (pFrameCropped == NULL)
        return -1;

    // Allocate an AVFrame structure
    pFrameRGB = avcodec_alloc_frame();
    if (pFrameRGB == NULL)
        return -1;

    // Determine required buffer size and allocate buffer
    numBytes = avpicture_get_size(PIX_FMT_RGB24, DisplaySizeX, DisplaySizeY);
    buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *) pFrameRGB, buffer, PIX_FMT_RGB24, 
                   DisplaySizeX, DisplaySizeY);

    pSwsCtx = sws_getContext(DisplaySizeX, DisplaySizeY, pCodecCtx->pix_fmt, 
                             DisplaySizeX, DisplaySizeY, PIX_FMT_RGB24, 
                             SWS_FAST_BILINEAR, NULL, NULL, NULL);


    if (pSwsCtx == NULL) {
        fprintf(stderr, "Cannot initialize the sws context\n");
        return -1;
    }

    // Read frames and save first five frames to disk
    i = 0;
    while (av_read_frame(pFormatCtx, &packet) >= 0)
    {
        // Is this a packet from the video stream?
        if (packet.stream_index == videoStream)
        {   // Decode video frame
            avcodec_decode_video2(pCodecCtx, pFrame, 
                                  &frameFinished, &packet);

            // Did we get a video frame?
            if (frameFinished)
            {
	      if (av_picture_crop((AVPicture *) pFrameCropped,
                                  (AVPicture *) pFrame, 
                                  PIX_FMT_YUV420P, crop_y, crop_x)< 0)
                {
                    fprintf(stderr, "error cropping picture\n");
                    return -1;
                }

                sws_scale(pSwsCtx,
                (const uint8_t * const *) pFrame->data,
                pFrame->linesize, 0, DisplaySizeY,
                pFrameRGB->data, pFrameRGB->linesize);

		// ConvertToRGB2(pFrameRGB, rgb, offsetx, offsety, crop_w, crop_h);
		ConvertToRGB(pFrameRGB, rgb, offsetx, offsety, crop_w, crop_h);
	      break;
            }
        }

    // Free the packet that was allocated by av_read_frame
    av_free_packet(&packet);
    }

    // Free the RGB image
    av_free(buffer);
    av_free(pFrameRGB);

    // Free the YUV frame
    av_free(pFrame);

    // Close the codec
    avcodec_close(pCodecCtx);

    // Close the video file
    avformat_close_input(&pFormatCtx);

    return 0;
}

void ConvertToRGB(AVFrame *pFrame, unsigned char*& rgb, int offsetx, int offsety, int width, int height)
{

  rgb = new unsigned char[height * width * 3];
  int count = 0;

  for (int h = offsety; h < offsety + height; h++){
    for(int x = 0; x < width * 3; x++){
      *(rgb + count) = *((unsigned char*)pFrame->data[0] + h * pFrame->linesize[0] + offsetx * 3 + x);
      count++;
    }
  }
}


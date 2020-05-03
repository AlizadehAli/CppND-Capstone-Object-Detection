#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H

#include "media_capture.h"

class VideoCapture : public MediaCapture
{
public:
  VideoCapture(std::string &video_path);
  bool GetNextFrame(cv::Mat &frame) override;
  ~VideoCapture(){};
};

#endif
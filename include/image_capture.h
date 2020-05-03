#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H

#include "media_capture.h"

class ImageCapture : public MediaCapture
{
public:
  ImageCapture(std::string &image_path);
  bool GetNextFrame(cv::Mat &frame) override;
  ~ImageCapture(){};
};

#endif
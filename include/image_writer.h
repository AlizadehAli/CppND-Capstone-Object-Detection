#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "media_writer.h"

class ImageWriter : public MediaWriter
{
public:
    ImageWriter(std::string &image_outpath);
    void WriteFrame(cv::Mat &frame) override;
};
#endif
#ifndef MEDIA_WRITER_H
#define MEDIA_WRITER_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

class MediaWriter
{
public:
    MediaWriter(){};
    MediaWriter(std::string &output_path);
    virtual void WriteFrame(cv::Mat &frame) = 0;
    ~MediaWriter(){};

protected:
    std::string output_path_{""};
};
#endif

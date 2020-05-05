#ifndef MEDIA_CAPTURE_H
#define MEDIA_CAPTURE_H

#include <fstream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//Base class to capture frames from image or video.
class MediaCapture
{
public:
    explicit MediaCapture(std::string &media_path);
    virtual bool GetNextFrame(cv::Mat &frame) = 0;
    bool EndOfFile();
    ~MediaCapture();

protected:
    bool end_of_file_;
    cv::VideoCapture cap_;
};
#endif
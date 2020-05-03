#include "video_capture.h"

VideoCapture::VideoCapture(std::string &video_path) : MediaCapture(video_path)
{
}

bool VideoCapture::GetNextFrame(cv::Mat &frame)
{
    if (!EndOfFile())
    {
        cap_ >> frame;
    }

    if (frame.empty())
    {
        end_of_file_ = true;
    }

    return EndOfFile();
}
#include "image_capture.h"

ImageCapture::ImageCapture(std::string &image_path) : MediaCapture(image_path)
{
}

bool ImageCapture::GetNextFrame(cv::Mat &frame)
{
    if (!EndOfFile())
    {
        cap_ >> frame;
    }

    end_of_file_ = true;
    return !EndOfFile();
}

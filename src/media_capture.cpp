#include "media_capture.h"

MediaCapture::MediaCapture(std::string &media_path)
{
    end_of_file_ = false;
    std::ifstream image_stream(media_path);
    if (image_stream)
    {
        cap_.open(media_path);
    }
}

bool MediaCapture::EndOfFile()
{
    return end_of_file_;
}

MediaCapture::~MediaCapture()
{
    cap_.release();
}
#ifndef VIDEO_WRITER_H
#define VIDEO_WRITER_H

#include "media_writer.h"

class VideoWriter : public MediaWriter
{
public:
    VideoWriter(std::string &video_outpath);
    void WriteFrame(cv::Mat &frame) override;
    void SetFrameDimensions(int width, int height);
    void OpenVideoStream();
    void CloseVideoStream();
    ~VideoWriter(){};

private:
    cv::VideoWriter video_writer_;
    int frame_height_{0};
    int frame_width_{0};
};
#endif
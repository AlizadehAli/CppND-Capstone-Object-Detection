#include "video_writer.h"

VideoWriter::VideoWriter(std::string &video_outpath) : MediaWriter(video_outpath)
{
}

VideoWriter::VideoWriter(const VideoWriter &other)
{
    video_writer_ = other.video_writer_;
    frame_width_ = other.frame_width_;
    frame_height_ = other.frame_height_;
}

VideoWriter::VideoWriter(VideoWriter &&other)
{
    video_writer_ = std::move(other.video_writer_);
    frame_width_ = std::move(other.frame_width_);
    frame_height_ = std::move(other.frame_height_);
}
void VideoWriter::WriteFrame(cv::Mat &frame)
{
    video_writer_.write(frame);
}

void VideoWriter::OpenVideoStream()
{
    video_writer_.open(output_path_, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frame_width_, frame_height_));
}
void VideoWriter::SetFrameDimensions(int width, int height)
{
    frame_width_ = width;
    frame_height_ = height;
}

void VideoWriter::CloseVideoStream()
{
    video_writer_.release();
}
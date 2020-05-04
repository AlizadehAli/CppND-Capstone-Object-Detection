#ifndef VIDEO_PROCESS_H
#define VIDEO_PROCESS_H

#include "object_detector.h"
#include "buffer.h"
#include "video_writer.h"
#include "object_detector.h"
#include "video_capture.h"
#include <future>
#include <thread>

class VideoProcess
{
public:
    std::string video_out = "out.avi";
    std::string kWinName = "Deep learning object detection in OpenCV";

    VideoProcess(std::unique_ptr<VideoCapture> capture, std::unique_ptr<ObjectDetector> object_detector);
    void Initialize();
    void RunThreads();
    ~VideoProcess();

private:
    void FrameRead();
    void ProcessFrame(std::promise<cv::Mat> prom, cv::Mat &frame);
    void ProcessThread();

    Buffer<cv::Mat> frame_buffer_;
    std::vector<std::thread> threads_;
    std::unique_ptr<VideoCapture> capture_{nullptr};
    std::unique_ptr<VideoWriter> video_writer_{nullptr};
    std::unique_ptr<ObjectDetector> object_detector_{nullptr};
};
#endif
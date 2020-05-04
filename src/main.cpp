#include <fstream>
#include <sstream>
#include <iostream>

#include "video_capture.h"
#include "video_writer.h"
#include "object_detector.h"
#include "buffer.h"
#include "video_process.h"
#include <memory>

enum MediaType
{
    image = 0,
    video = 1
};

Buffer<cv::Mat> frame_buffer;
std::string video_out = "out.avi";
std::string image_out = "out.jpg";

int main(int argc, char **argv)
{
    std::cout << "Hello World \n";

    std::string video_path("../data/run.mp4");
    std::unique_ptr<VideoCapture> capture = std::make_unique<VideoCapture>(video_path);
    //VideoCapture capture(video_path);

    static const std::string kWinName = "Deep learning object detection in OpenCV";
    cv::namedWindow(kWinName, cv::WINDOW_NORMAL);

    std::string config_path{"../data/yolov3-tiny.cfg"};
    std::string weights_path{"../data/yolov3-tiny.weights"};
    std::string classes_path{"../data/object_detection_classes_yolov3.txt"};

    std::unique_ptr<ObjectDetector> detector = std::make_unique<ObjectDetector>(config_path, weights_path, classes_path);

    VideoProcess video_process(std::move(capture), std::move(detector));
    video_process.RunThreads();
    return 0;
}
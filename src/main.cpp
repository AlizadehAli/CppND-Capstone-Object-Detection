#include <fstream>
#include <sstream>
#include <iostream>

#include "video_capture.h"

int main(int argc, char **argv)
{
    std::cout << "Hello World \n";

    std::string video_path("/Users/anuragkankanala/Documents/Udacity_C++_Nanodegree/CppND-Capstone/data/run.mp4");
    VideoCapture capture(video_path);

    static const std::string kWinName = "Deep learning object detection in OpenCV";
    cv::namedWindow(kWinName, cv::WINDOW_NORMAL);

    cv::Mat frame;
    capture.GetNextFrame(frame);

    while (cv::waitKey(1) < 0)
    {
        cv::imshow(kWinName, frame);
    }

    return 0;
}
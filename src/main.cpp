#include <fstream>
#include <sstream>
#include <iostream>

#include "video_capture.h"
#include "image_capture.h"
#include "image_writer.h"
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

const char *keys =
    "{help h usage ? | | Usage examples: \n\t\t./ObjectDetector --image=../data/bird.jpg \n\t\t./ObjectDetector --video=../data/run.mp4}"
    "{image i        |<none>| input image   }"
    "{video v       |<none>| input video   }";

Buffer<cv::Mat> frame_buffer;
std::string video_out = "out.avi";
std::string image_out = "out.jpg";
std::string config_path{"../data/yolov3-tiny.cfg"};
std::string weights_path{"../data/yolov3-tiny.weights"};
std::string classes_path{"../data/object_detection_classes_yolov3.txt"};

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Use this script to run object detection in OpenCV.");

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    else if (parser.has("image"))
    {
        std::string input = parser.get<std::string>("image");
        std::ifstream image_stream(input);
        if (!image_stream)
        {
            std::cout << "Invalid Image Path!!!\n";
            return 0;
        }

        std::unique_ptr<ImageCapture> image_capture = std::make_unique<ImageCapture>(input);
        cv::Mat frame;
        image_capture->GetNextFrame(frame);

        std::unique_ptr<ObjectDetector> detector = std::make_unique<ObjectDetector>(config_path, weights_path, classes_path);
        cv::Mat detected_frame = detector->DetectObjects(frame);

        std::unique_ptr<ImageWriter> image_writer = std::make_unique<ImageWriter>(image_out);
        image_writer->WriteFrame(detected_frame);

        static const std::string kWinName = "Deep learning object detection in OpenCV";
        cv::namedWindow(kWinName, cv::WINDOW_NORMAL);
        imshow(kWinName, frame);
        cv::waitKey(3000);
        cv::destroyAllWindows();

        std::cout << "Image Written to " << image_out << "\n";

        return 0;
    }

    else if (parser.has("video"))
    {
        std::string input = parser.get<std::string>("video");
        std::ifstream video_stream(input);
        if (!video_stream)
        {
            std::cout << "Invalid Video Path!!!\n";
            return 0;
        }

        std::unique_ptr<VideoCapture> capture = std::make_unique<VideoCapture>(input);
        std::unique_ptr<ObjectDetector> detector = std::make_unique<ObjectDetector>(config_path, weights_path, classes_path);

        VideoProcess video_process(std::move(capture), std::move(detector));
        video_process.RunThreads();
        return 0;
    }

    else
    {
        std::cout << "Invalid Input Parameters\n";
    }
}
#include "video_process.h"

VideoProcess::VideoProcess(std::unique_ptr<VideoCapture> capture, std::unique_ptr<ObjectDetector> object_detector)
{
    capture_ = std::move(capture);
    object_detector_ = std::move(object_detector);

    Initialize();
}

void VideoProcess::Initialize()
{
    video_writer_ = std::make_unique<VideoWriter>(video_out);
    video_writer_->SetFrameDimensions(capture_->GetFrameWidth(), capture_->GetFrameHeight());
    video_writer_->OpenVideoStream();
}

void VideoProcess::RunThreads()
{
    threads_.emplace_back(std::thread(&VideoProcess::FrameRead, this));
    threads_.emplace_back(std::thread(&VideoProcess::ProcessThread, this));
    threads_.emplace_back(std::thread(&VideoProcess::UIThread, this));
}

void VideoProcess::FrameRead()
{
    std::cout << "Frame reading thread started...\n";
    int num_frames{0};
    while (!capture_->EndOfFile())
    {
        cv::Mat frame;
        capture_->GetNextFrame(frame);
        frame_buffer_.add(std::move(frame));
        num_frames++;
    }
    frame_buffer_.SetEndOfFile(true);
    std::cout << "File read finished. Read frames : " << num_frames << "\n";
}

void VideoProcess::ProcessThread()
{
    while (!frame_buffer_.EndOfBuffer())
    {
        cv::Mat frame_to_process = frame_buffer_.pop();
        if (!frame_to_process.empty())
        {
            std::promise<cv::Mat> promise;
            std::future<cv::Mat> future = promise.get_future();

            //TODO can spawn multiple threads later
            std::thread t(&VideoProcess::ProcessFrame, this, std::move(promise), std::ref(frame_to_process));
            cv::Mat detected_frame = future.get();
            t.join();

            ui_frame_ = detected_frame.clone();
            video_writer_->WriteFrame(detected_frame);
        }

        // cv::imshow(kWinName, detected_frame);
        // cv::waitKey(30);
    }
    video_writer_->CloseVideoStream();
}

void VideoProcess::UIThread()
{
    std::cout << "Starting UI Thread...\n";
    cv::waitKey(1000);
    static const std::string kWinName = "Deep learning object detection in OpenCV";
    cv::namedWindow(kWinName, cv::WINDOW_NORMAL);
    while (true)
    {
        if (cv::waitKey(50) >= 0)
            break;
        cv::imshow(kWinName, ui_frame_);
    }
}

void VideoProcess::ProcessFrame(std::promise<cv::Mat> prom, cv::Mat &frame)
{
    cv::Mat detected_frame = object_detector_->DetectObjects(frame);
    prom.set_value(std::move(detected_frame));
}

VideoProcess::~VideoProcess()
{
    for (auto &thread : threads_)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
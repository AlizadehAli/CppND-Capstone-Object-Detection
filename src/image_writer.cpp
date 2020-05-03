#include "image_writer.h"

ImageWriter::ImageWriter(std::string &image_outpath) : MediaWriter(image_outpath) {}

void ImageWriter::WriteFrame(cv::Mat &frame)
{
    cv::imwrite(output_path_, frame);
}
#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <fstream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ObjectDetector
{
    const int inpWidth = 416;        // Width of network's input image
    const int inpHeight = 416;       // Height of network's input image
    const float confThreshold = 0.5; // Confidence threshold
    const float nmsThreshold = 0.4;  // Non-maximum suppression threshold

public:
    ObjectDetector() = delete;
    ObjectDetector(std::string &model_config, std::string &model_weights, std::string &classes_file); //default comstructor
    ObjectDetector(const ObjectDetector &other);                                                      //copy constructor
    ObjectDetector &operator=(const ObjectDetector &other);                                           //copy asignment operator
    ObjectDetector(ObjectDetector &&other);                                                           //move constructor
    ObjectDetector &operator=(ObjectDetector &&other);                                                //move assignment operator
    ~ObjectDetector() {}

    cv::Mat DetectObjects(cv::Mat &frame);

private:
    void GetOutputLayerNames();
    void Get4DBlob(cv::Mat &frame, cv::Mat &blob);
    void PostProcess(cv::Mat &frame, const std::vector<cv::Mat> &outs);
    void DrawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat &frame);
    void ReadClassesFromFile();

    static std::vector<std::string> output_layer_names_;
    static std::vector<std::string> classes_;

    cv::dnn::Net net_;
    std::string model_config_{""};
    std::string model_weights_{""};
    std::string classes_file_{""};
};
#endif
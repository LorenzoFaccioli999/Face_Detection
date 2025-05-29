#ifndef DNN_FACE_DETECTOR_HPP
#define DNN_FACE_DETECTOR_HPP

#include "face_detector.hpp"
#include <opencv2/dnn.hpp>

class DNNFaceDetector : public FaceDetector {
public:
    DNNFaceDetector(const std::string& modelPath, const std::string& configPath);
    bool load() override;
    void detectAndDisplay(cv::Mat& frame) override;

private:
    std::string modelPath;
    std::string configPath;
    cv::dnn::Net net;
    float confidenceThreshold = 0.5;
};

#endif

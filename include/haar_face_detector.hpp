#ifndef HAAR_FACE_DETECTOR_HPP
#define HAAR_FACE_DETECTOR_HPP

#include "face_detector.hpp"
#include <vector>
#include <string>

class HaarFaceDetector : public FaceDetector {
public:
    explicit HaarFaceDetector(const std::string& cascadePath);
    bool load() override;
    void detectAndDisplay(cv::Mat& frame) override;

private:
    std::string cascadePath;
    cv::CascadeClassifier faceCascade;
    std::vector<cv::Rect> previousFaces;

    double computeIoU(const cv::Rect& a, const cv::Rect& b);
};

#endif

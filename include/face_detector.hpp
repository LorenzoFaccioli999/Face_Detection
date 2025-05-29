#ifndef FACE_DETECTOR_HPP
#define FACE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

class FaceDetector {
public:
    virtual ~FaceDetector() = default;
    virtual bool load() = 0;
    virtual void detectAndDisplay(cv::Mat& frame) = 0;
};

#endif

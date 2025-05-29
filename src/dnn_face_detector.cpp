#include "dnn_face_detector.hpp"

DNNFaceDetector::DNNFaceDetector(const std::string& modelPath, const std::string& configPath)
    : modelPath(modelPath), configPath(configPath) {}

bool DNNFaceDetector::load() {
    net = cv::dnn::readNetFromCaffe(configPath, modelPath);
    return !net.empty();
}

void DNNFaceDetector::detectAndDisplay(cv::Mat& frame) {
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300),
                                          cv::Scalar(104.0, 177.0, 123.0), false, false);

    net.setInput(blob);
    cv::Mat detections = net.forward();

    cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    for (int i = 0; i < detectionMat.rows; ++i) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > confidenceThreshold) {
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
            cv::rectangle(frame, cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)), cv::Scalar(0, 255, 0), 2);
        }
    }
}

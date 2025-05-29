#include "haar_face_detector.hpp"

HaarFaceDetector::HaarFaceDetector(const std::string& cascadePath)
    : cascadePath(cascadePath) {}

bool HaarFaceDetector::load() {
    return faceCascade.load(cascadePath);
}

double HaarFaceDetector::computeIoU(const cv::Rect& a, const cv::Rect& b) {
    int x1 = std::max(a.x, b.x);
    int y1 = std::max(a.y, b.y);
    int x2 = std::min(a.x + a.width, b.x + b.width);
    int y2 = std::min(a.y + a.height, b.y + b.height);

    int intersectionArea = std::max(0, x2 - x1) * std::max(0, y2 - y1);
    int unionArea = a.area() + b.area() - intersectionArea;

    return unionArea > 0 ? static_cast<double>(intersectionArea) / unionArea : 0.0;
}

void HaarFaceDetector::detectAndDisplay(cv::Mat& frame) {
    std::vector<cv::Rect> faces;
    cv::Mat gray;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);

    faceCascade.detectMultiScale(gray, faces, 1.1, 6, 0, cv::Size(50, 50));

    std::vector<cv::Rect> stableFaces;
    for (const auto& face : faces) {
        for (const auto& prev : previousFaces) {
            if (computeIoU(face, prev) > 0.4) {
                stableFaces.push_back(face);
                break;
            }
        }
    }

    if (previousFaces.empty() || stableFaces.empty()) {
        stableFaces = faces;
    }

    previousFaces = stableFaces;

    for (const auto& face : stableFaces) {
        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
    }
}

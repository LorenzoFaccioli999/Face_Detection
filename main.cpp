#include "face_detector.hpp"
#include "haar_face_detector.hpp"
#include "dnn_face_detector.hpp"

#include <memory>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    std::string method = (argc > 1) ? argv[1] : "dnn";

    std::unique_ptr<FaceDetector> detector;

    if (method == "haar") {
        detector = std::make_unique<HaarFaceDetector>("classifiers/haarcascade_frontalface_default.xml");
    } else if (method == "dnn") {
        detector = std::make_unique<DNNFaceDetector>(
        "models/res10_300x300_ssd_iter_140000.caffemodel",  // model (weights)
        "models/deploy.prototxt"                            // config (text)
    );

    } else {
        std::cerr << "Unknown detection method: " << method << std::endl;
        return 1;
    }

    if (!detector->load()) {
        std::cerr << "Failed to load detector!" << std::endl;
        return 1;
    }

    // use your camera:
    //cv::VideoCapture cap(0);

    // or use a file: 
    cv::VideoCapture cap("videos/test_video.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        detector->detectAndDisplay(frame);
        cv::imshow("Face Detection", frame);
        if (cv::waitKey(10) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

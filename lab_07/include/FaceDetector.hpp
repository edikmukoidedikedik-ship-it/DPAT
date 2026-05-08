#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class FaceDetector {
public:
    FaceDetector(const std::string& proto, const std::string& model);
    ~FaceDetector();

    void updateFrame(const cv::Mat& frame);
    
    std::vector<cv::Rect> getFaces();

private:
    void detectLoop(); 

    cv::dnn::Net net;
    cv::Mat frameToProcess;
    std::vector<cv::Rect> detectedFaces;
    
    std::thread workerThread;
    std::mutex dataMutex;
    std::atomic<bool> running;
    bool hasFrame = false;
};

#endif

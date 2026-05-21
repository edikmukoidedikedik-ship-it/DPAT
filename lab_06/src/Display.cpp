#include "Display.hpp"

Display::Display(const std::string& windowName) : winName(windowName) {
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Brightness", winName, &brightness, 100);
}

void Display::show(const cv::Mat& frame) {
    if (!frame.empty()) {
        cv::imshow(winName, frame);
    }
}

void Display::drawOverlay(cv::Mat& frame, const std::string& text) {
    cv::putText(frame, text, cv::Point(20, 40), 
                cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
}

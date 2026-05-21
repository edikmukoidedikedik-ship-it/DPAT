#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <opencv2/opencv.hpp>
#include <string>

class Display {
public:
    Display(const std::string& windowName);
    void show(const cv::Mat& frame);
    void drawOverlay(cv::Mat& frame, const std::string& text);
    int brightness = 50;
private:
    std::string winName;
};

#endif

#include "FrameProcessor.hpp"

void FrameProcessor::process(cv::Mat& input, cv::Mat& output, ProcessMode mode, int brightness) {

    cv::Mat tempEffect;

    switch (mode) {
        case ProcessMode::INVERSION:
            cv::bitwise_not(input, tempEffect);
            break;

        case ProcessMode::GAUSSIAN_BLUR:
            cv::GaussianBlur(input, tempEffect, cv::Size(15, 15), 0);
            break;

        case ProcessMode::CANNY_FILTER:
            cv::cvtColor(input, tempEffect, cv::COLOR_BGR2GRAY);
            cv::Canny(tempEffect, tempEffect, 100, 200);
            break;

        case ProcessMode::GRAYSCALE:
            cv::cvtColor(input, tempEffect, cv::COLOR_BGR2GRAY);
            break;

        case ProcessMode::NONE:
        default:
            tempEffect = input.clone();
            break;
    }

    tempEffect.convertTo(output, -1, 1, brightness - 50);
}

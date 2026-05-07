#ifndef FRAME_PROCESSOR_HPP
#define FRAME_PROCESSOR_HPP

#include <opencv2/opencv.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
public:
   void process(cv::Mat& input, cv::Mat& output, ProcessMode mode, int brightness);
};

#endif

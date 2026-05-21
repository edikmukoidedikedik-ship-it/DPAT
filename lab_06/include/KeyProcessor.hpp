#ifndef KEY_PROCESSOR_HPP
#define KEY_PROCESSOR_HPP

#include <opencv2/opencv.hpp>

enum class ProcessMode {
    NONE,
    INVERSION,
    GAUSSIAN_BLUR,
    CANNY_FILTER,
    GRAYSCALE,
    EXIT
};

class KeyProcessor {
public:
    KeyProcessor();

    ProcessMode getMode(int key);

private:
    ProcessMode currentMode;
};

#endif

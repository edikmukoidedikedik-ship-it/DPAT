#ifndef KEYPROCESSOR_HPP
#define KEYPROCESSOR_HPP

#include <opencv2/opencv.hpp>
#include <string>

enum class ProcessMode {
    NONE,
    INVERSION,
    GAUSSIAN_BLUR,
    CANNY_FILTER,
    GRAYSCALE,
    FACE_DETECTION,
    EXIT
};

class KeyProcessor {
public:
    KeyProcessor();
  
    void handleInput();

    ProcessMode getCurrentMode() const;
    
    std::string getModeString() const;

private:
    ProcessMode currentMode;
};

#endif

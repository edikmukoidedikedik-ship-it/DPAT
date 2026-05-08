#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() : currentMode(ProcessMode::NONE) {}

void KeyProcessor::handleInput() {
    int key = cv::waitKey(1);
    if (key == -1) return; 

    switch (key) {
        case 27:  currentMode = ProcessMode::EXIT; break; 
        case '0': currentMode = ProcessMode::NONE; break;
        case '1': currentMode = ProcessMode::INVERSION; break;
        case '2': currentMode = ProcessMode::GAUSSIAN_BLUR; break;
        case '3': currentMode = ProcessMode::CANNY_FILTER; break;
        case '4': currentMode = ProcessMode::GRAYSCALE; break;
        case '5':
        case 'f': currentMode = ProcessMode::FACE_DETECTION; break;
        default: break;
    }
}

ProcessMode KeyProcessor::getCurrentMode() const {
    return currentMode;
}

std::string KeyProcessor::getModeString() const {
    switch (currentMode) {
        case ProcessMode::NONE:           return "Original";
        case ProcessMode::INVERSION:      return "Inversion";
        case ProcessMode::GAUSSIAN_BLUR:  return "Gaussian Blur";
        case ProcessMode::CANNY_FILTER:   return "Canny Filter";
        case ProcessMode::GRAYSCALE:      return "Grayscale";
        case ProcessMode::FACE_DETECTION: return "Face Detection";
        case ProcessMode::EXIT:           return "Exiting...";
        default:                          return "Unknown";
    }
}

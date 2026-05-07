#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() : currentMode(ProcessMode::NONE) {}

ProcessMode KeyProcessor::getMode(int key) {
    if (key == -1) return currentMode;

    switch (key) {
        case 27:          currentMode = ProcessMode::EXIT; break;
        case '0':         currentMode = ProcessMode::NONE; break;
        case '1':         currentMode = ProcessMode::INVERSION; break;
        case '2':         currentMode = ProcessMode::GAUSSIAN_BLUR; break;
        case '3':         currentMode = ProcessMode::CANNY_FILTER; break;
        case '4':         currentMode = ProcessMode::GRAYSCALE; break;
        default: break;
    }
    return currentMode;
}

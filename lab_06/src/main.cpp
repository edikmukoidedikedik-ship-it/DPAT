#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include <iostream>

int main() {
    CameraProvider camera(0);
    KeyProcessor keyHandler;
    FrameProcessor processor;
    Display display("Lab 6 - OpenCV");

    if (!camera.isOpened()) {
        std::cerr << "Помилка: Камера не знайдена!" << std::endl;
        return -1;
    }

    cv::Mat rawFrame;
    cv::Mat processedFrame;

    while (true) {
        if (!camera.getFrame(rawFrame)) break;

        // Обробка клавіш
        int key = cv::waitKey(30);
        ProcessMode mode = keyHandler.getMode(key);

        if (mode == ProcessMode::EXIT) break;

        processor.process(rawFrame, processedFrame, mode, display.brightness);

        std::string modeText = "Mode: " + std::to_string((int)mode);
        display.drawOverlay(processedFrame, modeText);

        display.show(processedFrame);
    }

    return 0;
}

#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"
#include "Display.hpp"
#include "FaceDetector.hpp"

int main() {

    CameraProvider camera(0); 
    FrameProcessor processor;
    KeyProcessor keys;
    Display display("Lab 7 - Computer Vision & Threads");

    FaceDetector faceDetector("deploy.prototxt", "res10_300x300_ssd_iter_140000.caffemodel");

    cv::Mat rawFrame, processedFrame;

    while (true) {
   
        if (!camera.getFrame(rawFrame)) {

            cv::putText(rawFrame, "Camera not found!", cv::Point(50, 50), 
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            if (rawFrame.empty()) break; 
        }

        keys.handleInput();
        ProcessMode mode = keys.getCurrentMode();

        if (mode == ProcessMode::EXIT) break;

        processor.process(rawFrame, processedFrame, mode, display.brightness);

        if (mode == ProcessMode::FACE_DETECTION) {

            faceDetector.updateFrame(rawFrame);

            std::vector<cv::Rect> faces = faceDetector.getFaces();

            for (const auto& face : faces) {
                cv::rectangle(processedFrame, face, cv::Scalar(0, 255, 0), 2);
                cv::putText(processedFrame, "Face Detected", cv::Point(face.x, face.y - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
            }
        }

        display.drawOverlay(processedFrame, keys.getModeString());
        display.show(processedFrame);
    }

    return 0;
}

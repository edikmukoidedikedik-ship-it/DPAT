cmake_minimum_required(VERSION 3.10)

project(OpenCV_Lab6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

set(SOURCES
    src/main.cpp
    src/CameraProvider.cpp
    src/FrameProcessor.cpp
    src/KeyProcessor.cpp
    src/Display.cpp
    src/FaceDetector.cpp
)

add_executable(opencv_lab ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(opencv_lab ${OpenCV_LIBS} Threads::Threads)

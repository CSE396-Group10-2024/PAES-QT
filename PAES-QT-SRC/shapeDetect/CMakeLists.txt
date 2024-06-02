cmake_minimum_required(VERSION 3.10)
project(DetectShapes)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add executable
add_executable(detect_shapes detect_shapes.cpp)

# Link OpenCV libraries
target_link_libraries(detect_shapes ${OpenCV_LIBS})


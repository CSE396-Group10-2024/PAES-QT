cmake_minimum_required(VERSION 3.5)

set(ProjectName "pose_generator")
project(${ProjectName})
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package

# Add the executable

# Link OpenCV libraries


# Select build system and set compile options

# Create executable file
add_executable(${ProjectName} pose_generator.cpp)

# Link ImageProcessor module
add_subdirectory(./src src)
target_include_directories(${ProjectName} PUBLIC ./src)
target_link_libraries(${ProjectName} src )



# For OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(${ProjectName} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${ProjectName} ${OpenCV_LIBS})

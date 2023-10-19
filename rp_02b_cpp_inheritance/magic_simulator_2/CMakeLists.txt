cmake_minimum_required(VERSION 2.8.3)
project(simple_simulator)

include_directories(/usr/include/eigen3)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_subdirectory(src)

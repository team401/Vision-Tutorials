cmake_minimum_required(VERSION 3.4)
project(FRC_Vision)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

find_package(OpenCV REQUIRED)
set(MAIN_FILE src/main.cpp)
set(HSV_FILE src/hsvFinder.cpp)
set(FL_FILE src/flCalculator.cpp)

add_executable(vision ${MAIN_FILE})
add_executable(hsvFinder ${HSV_FILE})
add_executable(flCalculator ${FL_FILE})

target_link_libraries(vision ${OpenCV_LIBS})
target_link_libraries(hsvFinder ${OpenCV_LIBS})
target_link_libraries(flCalculator ${OpenCV_LIBS})
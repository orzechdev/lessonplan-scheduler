cmake_minimum_required(VERSION 3.9)
project(algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(algorithm main.cpp include/algorithm/LessonplanScheduler.h src/LessonplanScheduler.cpp)
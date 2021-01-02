cmake_minimum_required(VERSION 3.17)
project(Algorithms_LFU_MFU)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algorithms_LFU_MFU main.cpp Algorithms.h Algorithms.cpp Controller.h Controller.cpp File_operation.h File_operation.cpp)
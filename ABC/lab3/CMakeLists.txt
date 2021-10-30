cmake_minimum_required(VERSION 3.16)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3
        cmake-build-debug/inp.txt
        cmake-build-debug/input.txt
        cmake-build-debug/output.txt
        main.cpp)

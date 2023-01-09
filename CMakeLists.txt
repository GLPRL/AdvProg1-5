cmake_minimum_required(VERSION 3.23)
project(AdvProg1_4)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvProg1_4 KnnServer/MainDistance.cpp
        KnnServer/Algorithms.h
        KnnServer/Algorithms.cpp
        KnnServer/TypeVector.h
        KnnServer/TypeVector.cpp
        KnnServer/knnServer.cpp KnnServer/knnServer.h KnnServer/MainDistance.h)

cmake_minimum_required(VERSION 3.23)
project(AdvProg1_4)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvProg1_4 KnnServer/MainDistance.cpp
        KnnServer/Algorithms.h
        KnnServer/Algorithms.cpp
        KnnServer/TypeVector.h
        KnnServer/TypeVector.cpp
        KnnServer/knnServer.cpp KnnServer/knnServer.h KnnServer/MainDistance.h KnnServer/Command/Command.h KnnServer/IO/DefaultIO.h KnnServer/IO/StandardIO.cpp KnnServer/IO/StandardIO.h KnnServer/IO/SocketIO.cpp KnnServer/IO/SocketIO.h KnnServer/Command/ClassifyData.cpp KnnServer/ClientData.cpp KnnServer/ClientData.h)

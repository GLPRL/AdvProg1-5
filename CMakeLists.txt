cmake_minimum_required(VERSION 3.23)
project(AdvProg1-5)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvProg1-5 KnnServer/MainDistance.cpp
        KnnServer/Algorithms.h
        KnnServer/Algorithms.cpp
        KnnServer/TypeVector.h
        KnnServer/TypeVector.cpp
        KnnServer/knnServer.cpp
        KnnServer/knnServer.h
        KnnServer/MainDistance.h
        KnnServer/Command/Command.h
        KnnServer/IO/DefaultIO.h
        KnnServer/IO/StandardIO.cpp
        KnnServer/IO/StandardIO.h
        KnnServer/IO/SocketIO.cpp
        KnnServer/IO/SocketIO.h
        KnnServer/Command/ClassifyData.cpp
        KnnServer/Client.cpp
        KnnServer/Client.h
        KnnServer/CLI.h
        KnnServer/Client.cpp
        KnnServer/Command/UploadData.cpp KnnServer/Command/SendData.h)
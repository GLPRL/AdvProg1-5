cmake_minimum_required(VERSION 3.23)
project(AdvProg1-5)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvProg1-5 MainDistance.cpp
        Algorithms.h
        Algorithms.cpp
        TypeVector.h
        TypeVector.cpp
        knnServer.cpp
        knnServer.h
        MainDistance.h
        Command/Command.h
        IO/DefaultIO.h
        IO/StandardIO.cpp
        IO/StandardIO.h
        IO/SocketIO.cpp
        IO/SocketIO.h
        Command/ClassifyData.cpp
        Client.cpp
        Client.h
        CLI.h
        Client.cpp
        Command/UploadData.cpp
        Command/SendSaveData.h
        Command/SendnSaveData.h)
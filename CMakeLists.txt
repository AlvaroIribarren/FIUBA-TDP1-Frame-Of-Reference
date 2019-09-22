cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/alvaro/CLionProjects/FrameOfReferenceTP")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -pthread")

add_executable(FrameOfReference main.cpp File.cpp File.h Vector.cpp Vector.h Binary.cpp Binary.h Block.cpp Block.h Nodo.h Controller.cpp Controller.h Thread.h FileProtected.cpp FileProtected.h BlockProtected.cpp BlockProtected.h SafeQueue.h NormalQueue.h)

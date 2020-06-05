cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/alvaro/CLionProjects/FrameOfReference")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -pthread")

add_executable(FrameOfReference main.cpp File.cpp File.h Vector.cpp Vector.h Block.cpp Block.h ThreadManager.cpp ThreadManager.h FileProtected.cpp FileProtected.h SafeQueue.h Thread.h ProcessorThread.cpp ProcessorThread.h WriterThread.cpp WriterThread.h)

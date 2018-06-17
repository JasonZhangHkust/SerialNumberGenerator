cmake_minimum_required(VERSION 3.10)
project(untitled)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)
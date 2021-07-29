cmake_minimum_required(VERSION 3.5)

project(PBF_Task_Client LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(PBF_Task_Client main.cpp tcpsocket.h tcpsocket.cpp message.h message.cpp)


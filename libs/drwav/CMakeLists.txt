cmake_minimum_required(VERSION 3.10)
project(dr_wav C CXX)

add_library(dr_wav STATIC DrWavImpl.cpp)
target_include_directories(dr_wav PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
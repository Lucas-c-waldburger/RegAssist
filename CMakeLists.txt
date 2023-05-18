cmake_minimum_required(VERSION 3.24)
project(RegAssist)

set(CMAKE_CXX_STANDARD 20)

add_executable(RegAssist main.cpp RegAssist.cpp RegAssist.h RangeTools.cpp RangeTools.h)

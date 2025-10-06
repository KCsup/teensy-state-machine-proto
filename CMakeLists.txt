cmake_minimum_required(VERSION 3.30)


project(teensy_sm_proto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(teensy_sm_proto
    src/main.cpp
)


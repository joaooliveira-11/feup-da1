cmake_minimum_required(VERSION 3.21)
project(DA_proj1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_proj1 main.cpp Classes/Segment.h Classes/Segment.cpp Classes/Station.h Classes/Station.cpp Classes/Reading.h Classes/Reading.cpp Classes/Network.h Classes/Network.cpp Classes/Menu.h Classes/Menu.cpp)

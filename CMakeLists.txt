cmake_minimum_required(VERSION 3.23)
project(railway)

set(CMAKE_CXX_STANDARD 14)

add_executable(railway main.cpp Station.cpp Station.h Segment.cpp Segment.h Graph.cpp Graph.h Management.cpp Management.h)

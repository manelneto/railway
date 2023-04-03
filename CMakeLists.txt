cmake_minimum_required(VERSION 3.23)
project(railway)

set(CMAKE_CXX_STANDARD 14)

add_executable(railway main.cpp Edge.h Edge.cpp Graph.h Graph.cpp Management.h Management.cpp MutablePriorityQueue.h MutablePriorityQueue.cpp Station.h Station.cpp Vertex.h Vertex.cpp)

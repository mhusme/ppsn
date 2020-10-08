cmake_minimum_required(VERSION 3.10.3)
project(Context)

set(CMAKE_CXX_STANDARD 11)
#adds zmq
find_package(cppzmq)

add_executable(Context main.cpp)

#linking libraries
target_link_libraries(Context cppzmq)
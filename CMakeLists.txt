project(graph)
cmake_minimum_required(VERSION 3.0)
add_definitions(-std=c++11)
add_definitions(-O3)
set(CMAKE_C_COMPILER_INIT g++)
include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(graph ${SOURCES})
target_link_libraries(graph Threads::Threads)

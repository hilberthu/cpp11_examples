cmake_minimum_required(VERSION 3.0)
project(lamda)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(lamda main.cpp)
#target_link_libraries(thread Threads::Threads)
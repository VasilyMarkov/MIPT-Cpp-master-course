cmake_minimum_required(VERSION 3.21)
project(Tuple)

find_package(Boost 1.74.0 REQUIRED) 

add_executable(Tuple main.cpp) 

target_include_directories(Tuple PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
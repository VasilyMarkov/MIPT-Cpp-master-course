cmake_minimum_required(VERSION 3.21)
project(Physical-quantities)

add_executable(Physical-quantities main.cpp) 

target_include_directories(Physical-quantities PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
cmake_minimum_required(VERSION 3.5)
project(cowString LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


add_executable(cowString main.cpp)

# target_include_directories(cowString PRIVATE ${CMAKE_SOURCE_DIR})

target_compile_features(cowString PUBLIC cxx_std_23)

# add_subdirectory(test)
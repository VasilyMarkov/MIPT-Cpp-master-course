cmake_minimum_required(VERSION 3.5)
project(cowString)

# set(CMAKE_CXX_FLAGS_DEBUG "-g -O2 -Wall -Wextra -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Boost 1.74.0 COMPONENTS tokenizer) 

add_executable(cowString main.cpp)

target_compile_features(cowString PUBLIC cxx_std_23)
target_link_libraries(cowString ${Boost_LIBRARIES})
add_subdirectory(test)
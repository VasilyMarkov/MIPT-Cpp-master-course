cmake_minimum_required(VERSION 3.21)
project(cowString)

if(SANITIZE)
    message("SANITIZE: ON")
else()
    message("SANITIZE: OFF")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Boost 1.74.0 COMPONENTS tokenizer) 

add_executable(cowString main.cpp)

target_link_libraries(cowString ${Boost_LIBRARIES})

if(TESTS)
    find_package(GTest REQUIRED)
    add_subdirectory(test)
    message("TESTING: ON")
else()
    message("TESTING: OFF")
endif()


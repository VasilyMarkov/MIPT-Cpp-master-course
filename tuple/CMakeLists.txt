cmake_minimum_required(VERSION 3.21)
project(Tuple)

find_package(Boost 1.74.0 COMPONENTS mpl) 

add_executable(Tuple main.cpp) 

target_include_directories(Tuple PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# if(TESTS)
#     find_package(GTest REQUIRED)
#     add_subdirectory(test)
#     message("TESTING: ON")
# else()
#     message("TESTING: OFF")
# endif()

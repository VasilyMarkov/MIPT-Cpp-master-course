cmake_minimum_required(VERSION 3.21)
project(Ram)

if(SANITIZE)
    message("SANITIZE: ON")
else()
    message("SANITIZE: OFF")
endif()

find_package(FLEX REQUIRED)

flex_target(scanner
  lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

add_executable(Ram main.cpp ${FLEX_scanner_OUTPUTS})

target_include_directories(Ram PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Ram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

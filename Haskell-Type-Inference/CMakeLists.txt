cmake_minimum_required(VERSION 3.21)
project(Haskell-Type-Inference)

if(SANITIZE)
    message("SANITIZE: ON")
else()
    message("SANITIZE: OFF")
endif()

# find_package(FLEX REQUIRED)

# flex_target(scanner
#   lexer.l
#   ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
# )

add_executable(Haskell-Type-Inference main.cpp 
    # ${FLEX_scanner_OUTPUTS}
)

target_include_directories(Haskell-Type-Inference PRIVATE 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# if(TESTS)
#     find_package(GTest REQUIRED)
#     add_subdirectory(test)
#     message("TESTING: ON")
# else()
#     message("TESTING: OFF")
# endif()

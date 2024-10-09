project(test)

find_package(FLEX REQUIRED)

flex_target(scanner
  ${CMAKE_SOURCE_DIR}/lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

add_executable(test 
  test.cpp 
  ${FLEX_scanner_OUTPUTS}
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(test PRIVATE GTest::gtest_main GTest::gtest)


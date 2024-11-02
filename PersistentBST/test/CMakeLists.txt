project(test)

add_executable(test 
  test.cpp 
  # ${CMAKE_SOURCE_DIR}/radix_sort.cpp
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(test PRIVATE GTest::gtest_main GTest::gtest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
message("Tests building...")

add_executable(test 
  test.cpp 
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(test PRIVATE gtest_main gmock_main)

target_compile_features(test PUBLIC cxx_std_23)

cmake_minimum_required(VERSION 3.21)
project(PersistentBST)

if(SANITIZE)
    message("SANITIZE: ON")
else()
    message("SANITIZE: OFF")
endif() 

if(TESTS)
   find_package(GTest REQUIRED)
   add_subdirectory(test)
   message("TESTING: ON")
else()
   message("TESTING: OFF")
endif()


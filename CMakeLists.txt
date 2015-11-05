cmake_minimum_required(VERSION 2.8)
project(capstone)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11")

set(SOURCE_FILES main.cpp)
add_executable(run_capstone ${SOURCE_FILES})

include_directories(capstone)

add_subdirectory(capstone)
add_subdirectory(capstone_tests)

#target_link_libraries(capstone_run capstone)
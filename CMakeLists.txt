cmake_minimum_required(VERSION 2.8.12)

project(saas)

IF(CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

add_subdirectory(lib)
add_subdirectory(sim)
add_subdirectory(saap)
add_subdirectory(cdti)

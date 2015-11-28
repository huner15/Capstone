include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_cdti_tests cdti_test.cpp)
target_link_libraries(run_cdti_tests cdti_lib gtest gtest_main)
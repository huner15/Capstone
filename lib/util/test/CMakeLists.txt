include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_util_tests vector_tests.cpp)
target_link_libraries(run_util_tests gtest gtest_main util_lib)
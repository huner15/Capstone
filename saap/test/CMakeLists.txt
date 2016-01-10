include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_saap_tests saap_test.cpp)
target_link_libraries(run_saap_tests gtest gtest_main)
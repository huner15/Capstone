add_executable(run_correlate_tests DistanceTest.cpp)

target_link_libraries(run_correlate_tests saap_lib gtest gtest_main util_lib
        categorize_lib)
target_include_directories(run_correlate_tests
        PUBLIC ${PROJECT_SOURCE_DIR}/../inc
        PUBLIC ${PROJECT_SOURCE_DIR}/../../receiver/inc)
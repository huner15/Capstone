include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_capstone_tests sample_test.cpp)

target_link_libraries(run_capstone_tests gtest gtest_main)
#target_link_libraries(run_capstone_tests capstone)
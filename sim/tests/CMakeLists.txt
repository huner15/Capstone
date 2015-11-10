
include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_sim_tests sim_test.cpp)

target_link_libraries(run_sim_tests sim_lib gtest gtest_main)
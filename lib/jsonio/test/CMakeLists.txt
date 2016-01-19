include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_flight_scenario_tests flight_scenario_tests.cpp)
target_link_libraries(run_flight_scenario_tests gtest gtest_main jsonio_lib)
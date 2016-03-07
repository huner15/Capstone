project(saap)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(run_correlate_tests ${SOURCE_FILES})
target_link_libraries(run_correlate_tests saap_lib gtest gtest_main util_lib
        categorize_lib gp_lib)
target_include_directories(run_correlate_tests
        PUBLIC ${PROJECT_SOURCE_DIR}/../inc
        PUBLIC ${PROJECT_SOURCE_DIR}/../../receiver/inc)
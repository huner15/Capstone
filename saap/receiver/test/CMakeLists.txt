include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../algorithm/inc)
add_executable(run_report_receiver_test ReportReceiverTests.cpp)
target_link_libraries(run_report_receiver_test gtest gtest_main util_lib)



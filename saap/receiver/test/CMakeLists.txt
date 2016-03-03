add_executable(run_report_receiver_test ReportReceiverTests.cpp)
target_link_libraries(run_report_receiver_test gtest gtest_main util_lib)
target_include_directories(run_report_receiver_test
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/../receiver/inc)


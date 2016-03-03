include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(run_report_receiver_test ${SOURCE_FILES} ReportReceiverTests.cpp)
target_link_libraries(run_report_receiver_test gtest gtest_main util_lib)


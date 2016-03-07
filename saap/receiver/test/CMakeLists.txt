include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
#file(GLOB SOURCE_FILES "../src/*.cpp")


SET(SOURCE_FILES ../src/ReportReceiver.cpp  ../src/SurveillanceReport.cpp
        ../test/ReportReceiverTests.cpp)

MESSAGE(${SOURCE_FILES})
add_executable(run_report_receiver_test ${SOURCE_FILES})
target_link_libraries(run_report_receiver_test gtest gtest_main util_lib)


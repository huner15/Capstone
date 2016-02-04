include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_util_tests VectorTests.cpp ../src/ActualReport.cpp ../inc/ActualReport.h ../inc/IntruderID.h ../inc/GeographicCoordinate.h ../src/SphericalCoordinate.cpp ../inc/SphericalCoordinate.h ../src/ActualFlight.cpp ../inc/ActualFlight.h ../src/ActualFlights.cpp ../inc/ActualFlights.h ../inc/RadarID.h)
target_link_libraries(run_util_tests gtest gtest_main util_lib)
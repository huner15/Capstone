include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
add_executable(run_util_tests VectorTests.cpp ../src/FlightReport.cpp ../inc/FlightReport.h ../inc/TcasID.h ../inc/GeographicCoordinate.h ../src/SphericalCoordinate.cpp ../inc/SphericalCoordinate.h ../src/Flight.cpp ../inc/Flight.h ../src/FlightSimulation.cpp ../inc/FlightSimulation.h ../inc/RadarID.h)
target_link_libraries(run_util_tests gtest gtest_main util_lib)
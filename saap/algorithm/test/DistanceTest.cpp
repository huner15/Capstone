/**
* @file CorrelationEngineTest.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-3-16
* @brief The tests for each of the Correlation Engine tests.
*/

#include <gtest/gtest.h>
#include "CorrelationEngine.h"

TEST(CalcHeading, tcasAndAdsb) {
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                            sphericalCoordinate, velocity,
                                             device);

    AdsBReport adsBReport = flightReport.CreateAdsBReport();

    EXPECT_EQ(time, adsBReport.timestamp());
    EXPECT_EQ(geographicCoordinate.GetLatitude(), adsBReport.latitude());
    EXPECT_EQ(geographicCoordinate.GetLongitude(), adsBReport.longitude());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), adsBReport.altitude());
    EXPECT_EQ(tailNumber.Get(), adsBReport.tail_number());
    EXPECT_EQ(velocity.north, adsBReport.north());
    EXPECT_EQ(velocity.down, adsBReport.down());
    EXPECT_EQ(velocity.east, adsBReport.east());
}
/**
* @file CorrelationEngineTest.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-3-16
* @brief The tests for each of the Correlation Engine tests.
*/

#include <gtest/gtest.h>
#include "CorrelationEngine.h"

TEST(TcasAdsb, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    Velocity velocity = Velocity();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    Velocity velocity = Velocity(100, 100, 100);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarAdsb, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    Velocity velocity = Velocity();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    Velocity velocity = Velocity(100, 100, 100);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarTcas, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    Velocity velocity = Velocity(100, 100, 100);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(TcasAdsb, inrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    Velocity velocity = Velocity();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(TcasAdsb, onrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    Velocity velocity = Velocity();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}
/**
* @file DistanceTests.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-3-16
* @brief The tests for each of the Correlation Engine distance metric tests.
*/

#include <gtest/gtest.h>
#include "CorrelationEngine.h"
#include "SurveillanceReport.h"

//TODO: add unconverted report tests
TEST(TcasAdsb, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID *radarID = NULL;
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
        *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
        *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(TcasAdsb, inrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID *radarID = NULL;
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(TcasAdsb, same) {
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

    device = TCAS;
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
        radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(1, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(TcasAdsb, onrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID *radarID = NULL;
    CorrelationEngine engine = CorrelationEngine();

    //test datas
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = TCAS;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      *radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarAdsb, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID *tcasID = NULL;
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarAdsb, inrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID *tcasID = NULL;
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarAdsb, onrange) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID *tcasID = NULL;
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarAdsb, same) {
    //setup data
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID *tcasID = NULL;
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    device = RADAR;
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, *tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(1, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarTcas, outofrange) {
    //setup data
    std::time_t time = 1;
    TailNumber *tailNumber = NULL;
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = TCAS;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarTcas, inrange) {
    //setup data
    std::time_t time = 1;
    TailNumber *tailNumber = NULL;
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = TCAS;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(100, 100, 100);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarTcas, onrange) {
    //setup data
    std::time_t time = 1;
    TailNumber *tailNumber = NULL;
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = TCAS;
    Velocity velocity = Velocity(1, 1, 1);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    SphericalCoordinate(100, 100, 100);
    device = RADAR;
    velocity = Velocity(40, 40, 40);
    geographicCoordinate = GeographicCoordinate(100, 100, 100);
    SurveillanceReport reportTwo = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(0, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(0, engine.CalcDistance(&reportOne, &reportTwo));
}

TEST(radarTcas, same) {
    //setup data
    std::time_t time = 1;
    TailNumber *tailNumber = NULL;
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    CorrelationEngine engine = CorrelationEngine();

    //test data
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(5, 10, 20);
    Device device = TCAS;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 10,
                                                                     20);
    SurveillanceReport reportOne = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    device = RADAR;
    SurveillanceReport reportTwo = SurveillanceReport(time, *tailNumber, tcasID,
                                                      radarID, geographicCoordinate, sphericalCoordinate, velocity, device);

    EXPECT_EQ(1, engine.CalcHeading(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcVelocity(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcEuclidDistance(&reportOne, &reportTwo));
    EXPECT_EQ(1, engine.CalcDistance(&reportOne, &reportTwo));
}

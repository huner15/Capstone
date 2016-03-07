/*
 * GenerationMathTests.cpp
 * Specific Atomics
 * Kevin Pham
 * 2-25-16
 * Tests for correct functionality in GenerationMath
 */

#include <gtest/gtest.h>
#include "GenerationMath.h"

TEST(ToRadian, PositiveNumber) {
    ASSERT_NEAR(1.1693705988, GenerationMath::ToRadians(67), .00000005);
    ASSERT_NEAR(6.2831853072, GenerationMath::ToRadians(360), .00000005);
}

TEST(ToRadian, NegativeNumber) {
    ASSERT_NEAR(-1.0471975512, GenerationMath::ToRadians(-60), .00000005);
    ASSERT_NEAR(-3.4033920414, GenerationMath::ToRadians(-195), .00000005);
}

TEST(ToRadian, Zero) {
    ASSERT_NEAR(0, GenerationMath::ToRadians(0), .00000005);
}

TEST(DistanceBetweenTwoCoordinates, SamePoint) {
    GeographicCoordinate coord1 (65, 145, 25000);
    GeographicCoordinate coord2 (65, 145, 25000);
    ASSERT_NEAR(0, GenerationMath::DistanceBetweenTwoCoordinates(
            coord1, coord2),.00000001);
}

TEST(DistanceBetweenTwoCoordinates, CloseBy) {
    GeographicCoordinate coord1 (65.2, 145, 25000);
    GeographicCoordinate coord2 (65.3, 145, 25000);
    std::cout << GenerationMath::DistanceBetweenTwoCoordinates(
            coord1, coord2) << std::endl;
    ASSERT_NEAR(36500.64, GenerationMath::DistanceBetweenTwoCoordinates(
            coord1, coord2),5);
}



TEST(ToDegrees, WholeNumbers) {
    ASSERT_NEAR(180, GenerationMath::ToDegrees(3.14159), .01);
    ASSERT_NEAR(57.2958, GenerationMath::ToDegrees(1), .01);
}


TEST(AbsoluteBearingBetweenTwoCoordinates, SameLatitude) {
    GeographicCoordinate coord1 (16, 16, 25000);
    GeographicCoordinate coord2 (12, 12, 25000);
    ASSERT_NEAR(224.63804446443481, GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
            coord1, coord2),.001);
}

TEST(AbsoluteBearingBetweenTwoCoordinates, BiggerNumbers) {
    GeographicCoordinate coord1 (2, 67, 25000);
    GeographicCoordinate coord2 (45, 78, 25000);
    ASSERT_NEAR(11.18329583708925, GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
            coord1, coord2),.001);
}

TEST(DestinationPoint, GoStraightNorth) {
    GeographicCoordinate coord1 (16, 16, 25000);
    Velocity vel (100, 100, 100);
    //GeographicCoordinate dest = GenerationMath::DestinationPoint(coord1, vel, 0);
    //std::cout << "\n" << dest.GetLatitude() << " " << dest.GetLongitude() << std::endl;
    //ASSERT_NEAR(16.004, dest.GetLatitude(),.005);
    //ASSERT_NEAR(16.0, dest.GetLongitude(),.005);
}

TEST(DestinationPoint, GoStraightEast) {
    GeographicCoordinate coord1 (16, 16, 25000);
    Velocity vel (100, 100, 100);
    //GeographicCoordinate dest = GenerationMath::DestinationPoint(coord1, vel, 90);
    //std::cout << "\n" << dest.GetLatitude() << " " << dest.GetLongitude() << std::endl;
    //ASSERT_NEAR(16.00, dest.GetLatitude(),.005);
    //ASSERT_NEAR(16.004, dest.GetLongitude(),.005);

    //GeographicCoordinate coord2 (123, 24, 345);
    GeographicCoordinate coord2 (50, 60, 100);
    GeographicCoordinate final = GenerationMath::DestinationPoint(coord2, Velocity(34, 0, 23), 270);
    //std::cout << "lat: " << final.GetLatitude() << " long: " << final.GetLongitude() << std::endl;

    GeographicCoordinate coord3 (89, 131, 345);
    GeographicCoordinate final2 = GenerationMath::DestinationPoint(coord3, Velocity(34, 0, 23), 270);
    //std::cout << "\nlat: " << final2.GetLatitude() << " long: " << final2.GetLongitude() << std::endl;
}




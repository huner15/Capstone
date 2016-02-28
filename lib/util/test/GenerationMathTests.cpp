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

TEST(DistanceBetweenTwoCoordinates, FarAway) {
    GeographicCoordinate coord1 (103, 35, 25000); //China
    GeographicCoordinate coord2 (77.016, 38.8833, 25000); //USA
    std::cout << GenerationMath::DistanceBetweenTwoCoordinates(
            coord1, coord2) << std::endl;
    ASSERT_NEAR(9479125.92, GenerationMath::DistanceBetweenTwoCoordinates(
            coord1, coord2),5);
}


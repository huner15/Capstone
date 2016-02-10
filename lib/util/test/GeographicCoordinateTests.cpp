/*
 * GeographicCoordinateTests.cpp
 * Specific Atomics
 * Kevin Pham
 * 2-9-16
 * Tests for correct functionality in GeographicCoordinate.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GeographicCoordinate.h"

TEST(GeographicCoordinateInputConstructor, ValidInput) {
    GeographicCoordinate coordinate (-145, 84, 25100);

    EXPECT_EQ(-145, coordinate.GetLatitude());
    EXPECT_EQ(84, coordinate.GetLongitude());
    EXPECT_EQ(25100, coordinate.GetAltitude());
}

TEST(GeographicCoordinateInputConstructor, ExceptionHandling) {
    try {
        GeographicCoordinate coordinate (-145, -184, 25100);
    }
    catch(std::domain_error const& error) {
        EXPECT_EQ(std::string("Value not in domain."), error.what());
    }
    catch(...) {
        FAIL() << "Expected std::domain_error";
    }
}


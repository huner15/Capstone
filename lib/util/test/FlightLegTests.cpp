/*
 * FlightLegTests.cpp
 * Specific Atomics
 * Kevin Pham
 * 2-9-16
 * Tests for correct functionality in FlightLeg.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlightLeg.h"

/*
 * Checks to make sure that a valid FlightLeg can be created.
 */
TEST(InputConstructor, ValidValues) {
    double duration_of_maneuver = 5;
    double duration_after_maneuver = 10;
    Vector3D velocity = {54.2, 43.7, 100.8};

    FlightLeg flight_leg (duration_of_maneuver,
                            duration_after_maneuver, velocity);

    EXPECT_EQ(duration_of_maneuver, flight_leg.GetDurationOfManeuver());
    EXPECT_EQ(duration_after_maneuver, flight_leg.GetDurationAfterManeuver());
    EXPECT_EQ(velocity.x, flight_leg.GetNewRelativeVelocity().x);
    EXPECT_EQ(velocity.y, flight_leg.GetNewRelativeVelocity().y);
    EXPECT_EQ(velocity.z, flight_leg.GetNewRelativeVelocity().z);
    //EXPECT_THAT(velocity, ContainerEq(flight_leg.GetNewRelativeVelocity()));
}

/**
 * Checks to make sure that negative durations throw the correct exception.
 */
TEST(InputConstructor, InvalidDurationValues) {
    double duration_of_maneuver = 1;
    double duration_after_maneuver = -2.0;
    Vector3D velocity = {54.2, 43.7, 100.8};

    try {
        FlightLeg flight_leg(duration_of_maneuver,
                             duration_after_maneuver, velocity);
    }
    catch(std::domain_error const& err) {
        EXPECT_EQ("Invalid duration value", err.what());
    }
    catch(...) {
        FAIL() << "Expected std::domain_error";
    }

}


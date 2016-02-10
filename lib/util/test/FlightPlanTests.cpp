/*
 * FlightPlanTests.cpp
 * Specific Atomics
 * Kevin Pham
 * 2-9-16
 * Tests for correct functionality in FlightPlan.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlightPlan.h"

TEST(FlightPlanInputConstructor, ValidValues) {
    FlightLeg flight_leg1 (5, 10, Vector3D {54.2, 43.7, 100.7});
    FlightLeg flight_leg2 (3, 2, Vector3D {2.5, 143.8, 29.1});
    GeographicCoordinate geographic_coordinate (130, 95, 2000);
    std::vector<FlightLeg> flight_legs;

    flight_legs.push_back(flight_leg1);
    flight_legs.push_back(flight_leg2);

    FlightPlan flight_plan (geographic_coordinate, flight_legs);

    EXPECT_EQ(130, flight_plan.GetStartPosition().GetLatitude());
    EXPECT_EQ(95, flight_plan.GetStartPosition().GetLongitude());
    EXPECT_EQ(2000, flight_plan.GetStartPosition().GetAltitude());

    EXPECT_EQ(2, flight_plan.GetFlightLegs().size());

    //TODO::Need a better way to do this.  Once I figure out GoogleMock I Should be able to compare collections.
   /* std::vector<FlightLeg>::iterator expected_iter = flight_legs.begin();
    std::vector<FlightLeg>::iterator actual_iter =
            flight_plan.GetFlightLegs().begin();

    for(; actual_iter != flight_plan.GetFlightLegs().end(); ++expected_iter, ++actual_iter) {
        EXPECT_EQ((*expected_iter).GetDurationOfManeuver(),
                  (*actual_iter).GetDurationOfManeuver());
        EXPECT_EQ((*expected_iter).GetDurationAfterManeuver(),
                  (*actual_iter).GetDurationAfterManeuver());
        EXPECT_EQ((*expected_iter).GetNewRelativeVelocity().x,
                  (*actual_iter).GetNewRelativeVelocity().x);
        EXPECT_EQ((*expected_iter).GetNewRelativeVelocity().y,
                  (*actual_iter).GetNewRelativeVelocity().y);
        EXPECT_EQ((*expected_iter).GetNewRelativeVelocity().z,
                  (*actual_iter).GetNewRelativeVelocity().z);

    }*/

}
/**
 * @file FlightPlanTests.cpp
 * @author Specific Atomics
 * @authors Kevin Pham, Frank Poole (just the velocity bug)
 * @date 2-16-16
 * @brief Tests for correct functionality in FlightPlan.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FlightPlan.h"

TEST(FlightPlanInputConstructor, ValidValues) {
    FlightLeg flight_leg1 (5, 10, Velocity {54.2, 43.7, 100.7});
    FlightLeg flight_leg2 (3, 2, Velocity {2.5, 143.8, 29.1});
    GeographicCoordinate geographic_coordinate (30, 95, 2000);
    std::vector<FlightLeg> flight_legs;

    flight_legs.push_back(flight_leg1);
    flight_legs.push_back(flight_leg2);

    FlightPlan flight_plan (geographic_coordinate, flight_legs);

    EXPECT_EQ(30, flight_plan.GetStartPosition().GetLatitude());
    EXPECT_EQ(95, flight_plan.GetStartPosition().GetLongitude());
    EXPECT_EQ(2000, flight_plan.GetStartPosition().GetAltitude());

    EXPECT_EQ(2, flight_plan.GetFlightLegs().size());

    /*std::cout << flight_plan.GetFlightLegs().at(1).GetDurationAfterManeuver() << std::endl;
    //TODO::Need a better way to do this.  Once I figure out GoogleMock I Should be able to compare collections.
    std::vector<FlightLeg>::iterator expected_iter = flight_legs.begin();
    std::vector<FlightLeg>::iterator actual_iter =
            flight_plan.GetFlightLegs().begin();
*/

    for(int idx = 0; idx < flight_legs.size(); idx++) {
        EXPECT_EQ(flight_legs.at(idx).GetDurationOfManeuver(),
                  flight_plan.GetFlightLegs().at(idx).GetDurationOfManeuver());
        EXPECT_EQ(flight_legs.at(idx).GetDurationAfterManeuver(),
                  flight_plan.GetFlightLegs().at(idx).GetDurationAfterManeuver());
        EXPECT_EQ(flight_legs.at(idx).GetNewRelativeVelocity().x,
                  flight_plan.GetFlightLegs().at(idx).GetNewRelativeVelocity().x);
        EXPECT_EQ(flight_legs.at(idx).GetNewRelativeVelocity().y,
                  flight_plan.GetFlightLegs().at(idx).GetNewRelativeVelocity().y);
        EXPECT_EQ(flight_legs.at(idx).GetNewRelativeVelocity().z,
                  flight_plan.GetFlightLegs().at(idx).GetNewRelativeVelocity().z);

    }

}

TEST(FlightPlanInputConstructor, ExceptionHandling) {
    try {
        FlightLeg flight_leg1 (5, 10, Velocity {54.2, 43.7, 100.7});
        GeographicCoordinate geographic_coordinate (30, 95, 2000);
        std::vector<FlightLeg> flight_legs;

        flight_legs.push_back(flight_leg1);

        FlightPlan flight_plan (geographic_coordinate, flight_legs);
    }
    catch(std::out_of_range const& err) {
        EXPECT_EQ("There must be atleast one flight leg", err.what());
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }

}

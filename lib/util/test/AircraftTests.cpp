/**
 * @file AircraftTests.cpp
 * @author Specific Atomics
 * @authors Kevin Pham, Frank Poole (just the velocity bug)
 * @date 2-16-16
 * @brief Tests for correct functionality in Aircraft.cpp.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Aircraft.h"

TEST(AircraftInputConstructor, ValidValues) {
    TailNumber tailNumber ("AAAAAA");
    FlightLeg flight_leg1 (5, 10, Velocity {54.2, 43.7, 100.7});
    FlightLeg flight_leg2 (3, 2, Velocity {2.5, 143.8, 29.1});
    GeographicCoordinate geographic_coordinate (45, 95, 2000);
    std::vector<FlightLeg> flight_legs;

    flight_legs.push_back(flight_leg1);
    flight_legs.push_back(flight_leg2);

    FlightPlan flight_plan (geographic_coordinate, flight_legs);
    bool hasAdsB = true;
    bool hasTcas = false;

    Aircraft aircraft (tailNumber, flight_plan, hasAdsB, hasTcas);

    ASSERT_TRUE(tailNumber == aircraft.GetTailNumber());
    ASSERT_TRUE(flight_plan == aircraft.GetFlightPlan());
    ASSERT_TRUE(hasAdsB);
    ASSERT_FALSE(hasTcas);
}

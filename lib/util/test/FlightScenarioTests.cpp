/**
 * @file FlightScenarioTests.cpp
 * @author Specific Atomics
 * @authors Kevin Pham, Frank Poole (just the velocity bug)
 * @date 2-16-16
 * @brief Tests for correct functionality in FlightScenario.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlightScenario.h"

TEST(FlightScenarioInputConstructor, ValidValues) {
    TailNumber tailNumber ("AAAAAA");
    FlightLeg flight_leg1 (5, 10, Velocity {54.2, 43.7, 100.7});
    FlightLeg flight_leg2 (3, 2, Velocity {2.5, 143.8, 29.1});
    GeographicCoordinate geographic_coordinate (130, 95, 2000);
    std::vector<FlightLeg> flight_legs;

    flight_legs.push_back(flight_leg1);
    flight_legs.push_back(flight_leg2);

    FlightPlan flight_plan (geographic_coordinate, flight_legs);
    bool hasAdsB = true;
    bool hasTcas = false;

    Aircraft aircraft (tailNumber, flight_plan, hasAdsB, hasTcas);

    TailNumber tailNumber2 ("111111");
    FlightLeg flight_leg3 (2, 7, Velocity {10.4, 100.9, 3.7});
    FlightLeg flight_leg4 (3, 2, Velocity {43.1, 54.1, 21.1});
    GeographicCoordinate geographic_coordinate2 (43, 78, 9000);
    std::vector<FlightLeg> flight_legs2;

    flight_legs2.push_back(flight_leg3);
    flight_legs2.push_back(flight_leg4);

    FlightPlan flight_plan2 (geographic_coordinate2, flight_legs2);
    bool hasAdsB2 = true;
    bool hasTcas2 = true;

    Aircraft aircraft2 (tailNumber2, flight_plan2, hasAdsB2, hasTcas2);

    std::vector<Aircraft> all_aircraft;
    all_aircraft.push_back(aircraft2);

    FlightScenario flight_scenario (aircraft, all_aircraft);

    ASSERT_TRUE(aircraft == flight_scenario.GetOwnship());
    for(int idx = 0; idx < all_aircraft.size(); idx++) {
        ASSERT_TRUE(all_aircraft.at(idx) ==
                            flight_scenario.GetAircraft().at(idx));
    }
}

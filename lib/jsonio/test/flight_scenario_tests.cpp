//
// Created by kevin on 1/18/16.
//

#include "FlightScenarioIO.h"
#include "gtest/gtest.h"

// Tests accessor function of absolute ownship data.
TEST(OwnshipData, CheckCorrectData) {
    Json::Value ownship = FlightScenarioIO::GetAbsoluteOwnshipData();
    EXPECT_FLOAT_EQ(ownship["latitude"].asFloat() , 73.60);
    EXPECT_FLOAT_EQ(ownship["longitude"].asFloat() , 34.45);
    EXPECT_FLOAT_EQ(ownship["altitude"].asFloat() , 18000);
}

TEST(GetsFlightPlans, CorrectNumberOfPositions) {
    std::vector<std::vector<int>> start_positions =
            FlightScenarioIO::GetStartPositions();

    ASSERT_EQ(2, start_positions.size());
}

TEST(GetsFlightPlans, CorrectData) {
    std::vector<std::vector<int>> start_positions =
            FlightScenarioIO::GetStartPositions();

    ASSERT_EQ(123, start_positions.at(0).at(0));
    ASSERT_EQ(24, start_positions.at(0).at(1));
    ASSERT_EQ(345, start_positions.at(0).at(2));
}

TEST(GetsFlightLegs, CorrectNumberOfLegs) {
    std::vector<Json::Value> flight_legs = FlightScenarioIO::GetFlightLegs();

    ASSERT_EQ(2, flight_legs.size());
}

TEST(GetsFlightLegs, CorrectData) {
    std::vector<Json::Value> flightLegs = FlightScenarioIO::GetFlightLegs();

    ASSERT_EQ(5, flightLegs[0][0]["durationOfManeuver"].asFloat());
    ASSERT_EQ(4, flightLegs[0][0]["durationAfterManeuver"].asFloat());
    ASSERT_EQ(34, flightLegs[0][0]["newRelativeVelocity"]["x"].asFloat());
    ASSERT_EQ(3, flightLegs[0][0]["newRelativeVelocity"]["y"].asFloat());
    ASSERT_EQ(23, flightLegs[0][0]["newRelativeVelocity"]["z"].asFloat());
}
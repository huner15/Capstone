/**
* @file SnapshotTest.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 3-6-16
* @brief The tests for each of the Correlation Engine tests.
*/

#include <gtest/gtest.h>
#include "Snapshot.h"

TEST(GetAircraft, Empty) {
    std::vector<CorrelationAircraft> aircraft;
    std::time_t timestamp;
    Snapshot snapshot = Snapshot(&aircraft, timestamp);
    EXPECT_EQ(snapshot.GetAircraft()->size(), 0);
}

TEST(GetAircraft, NonEmpty) {
    std::vector<CorrelationAircraft> aircraft;
    std::time_t timestamp;
    aircraft.push_back(CorrelationAircraft());
    Snapshot snapshot = Snapshot(&aircraft, timestamp);
//    for (int i = 0; i < aircraft.size(); i++) {
//        EXPECT_EQ(aircraft, snapshot.GetAircraft());
//    }
}

TEST(GetTimestamp, Empty) {
    std::vector<CorrelationAircraft> *aircraft;
    std::time_t timestamp;
    Snapshot snapshot = Snapshot(aircraft, timestamp);
    EXPECT_EQ(timestamp, snapshot.GetTimestamp());
}

TEST(GetTimestamp, NonEmpty) {
    std::vector<CorrelationAircraft> *aircraft;
    std::time_t timestamp;
    Snapshot snapshot = Snapshot(aircraft, timestamp);
    EXPECT_EQ(timestamp, snapshot.GetTimestamp());
}
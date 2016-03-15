/**
* @file PredictionTest.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 3-6-16
* @brief The tests for each of the Correlation Engine tests.
*/


#include <gtest/gtest.h>
#include "Prediction.h"

TEST(AddAircraft, Empty) {
//    Prediction prediction;
//    std::vector<CorrelationAircraft> aircraft;
//    CorrelationAircraft aircraft1;
//    EXPECT_EQ(prediction.AddAircraft(&aircraft1), 0);
//    EXPECT_EQ(aircraft.size(), 1);
}
TEST(AddAircraft, NonEmpty) {
//    Prediction prediction;
//    std::vector<CorrelationAircraft> aircraft;
//    aircraft.push_back(CorrelationAircraft());
//    CorrelationAircraft aircraft1;
//    EXPECT_EQ(prediction.AddAircraft(&aircraft1), 0);
//    EXPECT_EQ(prediction.GetCurrentSnapshot()->GetAircraft()->size(), 2);
}

TEST(TakeSnapshot, EmptyHistory) {
//    Prediction prediction;
//    std::vector<CorrelationAircraft> aircraft;
//    std::time_t timestamp;
//    prediction.TakeSnapshot();
//    EXPECT_EQ(prediction.GetSnapshotCounter(), 1);
//    EXPECT_EQ(prediction.GetHistory()->GetLast(), prediction.GetCurrentSnapshot());
}

TEST(TakeSnapshot, NonEmptyHistory) {
    Prediction prediction;
    std::vector<CorrelationAircraft> aircraft;
    std::time_t timestamp;
    EXPECT_EQ(prediction.GetSnapshotCounter(), 0);
    Snapshot *snapshot = prediction.GetCurrentSnapshot();
    prediction.TakeSnapshot();
    EXPECT_EQ(prediction.GetSnapshotCounter(), 1);
    EXPECT_EQ(prediction.GetHistory()->GetLast(), snapshot);
    snapshot = prediction.GetHistory()->GetLast();
    prediction.TakeSnapshot();
    EXPECT_EQ(prediction.GetSnapshotCounter(), 2);
    EXPECT_EQ(prediction.GetHistory()->GetLast(), prediction.GetCurrentSnapshot());
    EXPECT_EQ(prediction.GetHistory()->GetSecondToLast(), snapshot);
}

TEST(SearchTailNum, NoAircraft) {

}

TEST(SearchTailNum, NonExistentMultipleAircraft) {

}

TEST(SearchTailNum, ExistentMultipleAircraft) {

}

TEST(SearchRadarID, NoAircraft) {

}

TEST(SearchRadarID, NonExistentMultipleAircraft) {

}

TEST(SearchRadarID, ExistentMultipleAircraft) {

}

TEST(SearchTcasID, NoAircraft) {

}

TEST(SearchTcasID, NonExistentMultipleAircraft) {

}

TEST(SearchTcasID, ExistentMultipleAircraft) {

}

TEST(PredictVelocity, IsADSB) {

}

TEST(PredictVelocity, NotADSB) {
    Prediction prediction;
}

TEST(PredictionLocation, One) {

}
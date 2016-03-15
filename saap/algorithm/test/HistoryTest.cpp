/**
* @file HistoryTest.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 3-6-16
* @brief The tests for each of the Correlation Engine tests.
*/


#include <gtest/gtest.h>
#include "History.h"

TEST(GetLast, Empty) {
    History history;
    EXPECT_EQ(NULL, history.GetLast());
}

TEST(GetLast, NonEmpty) {
    History history;
    std::vector<CorrelationAircraft> aircraft;
    time_t timestamp;
    Snapshot snapshot = Snapshot(&aircraft, timestamp);
    history.AddSnapshot(&snapshot);
    EXPECT_EQ(history.GetLast(), &snapshot);
}

TEST(GetSecondLast, Empty) {
    History history;
    EXPECT_EQ(NULL, history.GetSecondToLast());
}

TEST(GetSecondLast, NonEmpty) {
    History history;
    std::vector<CorrelationAircraft> aircraft;
    time_t timestamp;
    Snapshot snapshot = Snapshot(&aircraft, timestamp);
    history.AddSnapshot(&snapshot);
    EXPECT_EQ(history.GetLast(), &snapshot);
}



//private:
//Snapshot *_last; /** The most recent Snapshot. */
//Snapshot *_second_to_last; /** The second most recent Snapshot. */
//
//public:
//History();
//~History();
///**
// * Accessor to the most recent Snapshot.
// *
// * @return The most recent Snapshot.
// */
//Snapshot *GetLast() const;
//
///**
// * Accessor to the second to most recent Snapshot.
// *
// * @return The second to most recent Snapshot.
// */
//Snapshot *GetSecondToLast() const;
//
///**
// * Accessor to the third to most recent Snapshot.
// *
// * @return The third to most recent Snapshot.
// */
//Snapshot *GetThirdToLast() const;
//
///**
// * Adds a Snapshot to the history and shifts subsequent Snapshots
// *
// * @return 0 on success and 1 on failure
// */
//int AddSnapshot(Snapshot *snapshot);

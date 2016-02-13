/*
 * TcasID.cpp
 * Specific Atomics
 * Frank Poole
 * 2-13-16
 * Ensures the functionality of TcasID.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TcasID.h"

/*
 * Test the default tcasID constructor by sequentially comparing three new
 * TCAS ID's to the previously the declared TCAS ID. As TCAS IDs are
 * randomly generated numbers, all three comparisons should be
 * inequivalent. Also ensures that generated TCAS identification integers are
 * from 1 to 25, the valid ID range.
 */
TEST(TcasIDDefaultConstructor, RandomGeneration) {
    TcasID current_tcas_id, last_tcas_id;

    last_tcas_id = current_tcas_id;
    current_tcas_id = TcasID ();
    EXPECT_NE(last_tcas_id.Get(), current_tcas_id.Get());
    EXPECT_TRUE(current_tcas_id.Get() > 0 && current_tcas_id.Get() <= 25);

    last_tcas_id = current_tcas_id;
    current_tcas_id = TcasID ();
    EXPECT_NE(last_tcas_id.Get(), current_tcas_id.Get());
    EXPECT_TRUE(current_tcas_id.Get() > 0 && current_tcas_id.Get() <= 25);

    last_tcas_id = current_tcas_id;
    current_tcas_id = TcasID ();
    EXPECT_NE(last_tcas_id.Get(), current_tcas_id.Get());
    EXPECT_TRUE(current_tcas_id.Get() > 0 && current_tcas_id.Get() <= 25);
}

/**
 * Test the input TcasID constructor by assigning both valid and invalid values.
 */
TEST(TcasIDInputConstructor, Assignment) {
    TcasID tcas_id (1);

    EXPECT_EQ(1, tcas_id.Get());

    tcas_id = TcasID (25);
    EXPECT_EQ(25, tcas_id.Get());

    try {
        tcas_id =TcasID (0);
    }
    catch (std::out_of_range const &exception) {
        EXPECT_EQ(std::string("Invalid TCAS ID. Valid TCAS IDs range from 0"
                                      " to 25 inclusive."),
                  exception.what());
    }

    try {
        tcas_id =TcasID (26);
    }
    catch (std::out_of_range const &exception) {
        EXPECT_EQ(std::string("Invalid TCAS ID. Valid TCAS IDs range from 0"
                                      " to 25 inclusive."),
                  exception.what());
    }
}

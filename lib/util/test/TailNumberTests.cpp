/*
 * TailNumberTests.cpp
 * Specific Atomics
 * Frank Poole
 * 2-9-16
 * Ensures the functionality of TailNumber.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TailNumber.h"

/**
 * Ensures that generated tail numbers are six characters in length.
 */
TEST(DefaultConstructor, Length) {
    TailNumber tail_number;
    EXPECT_EQ(6, tail_number.GetTailNumber().length());
}

/*
 * Test the default tail number constructor by sequentially comparing three new
 * tail numbers to the previously declared tail number. As tail numbers are
 * randomly generated alphanumeric characters, all three comparisons should be
 * inequivalent.
 */
TEST(DefaultConstruction, RandomGeneration) {
    TailNumber current_tail_number, last_tail_number;

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_NE(last_tail_number.GetTailNumber(),
              current_tail_number.GetTailNumber());

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_NE(last_tail_number.GetTailNumber(),
              current_tail_number.GetTailNumber());

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_NE(last_tail_number.GetTailNumber(),
              current_tail_number.GetTailNumber());
}

TEST(InputConstructor, Assignment) {
    TailNumber tail_number ("123456");
    EXPECT_EQ("123456", tail_number.GetTailNumber());
}

TEST(InputConstructor, OutOfRangeException) {
    try {
        TailNumber tail_number ("");
    }
    catch (std::out_of_range const &exception) {
        EXPECT_EQ(std::string("Tail Number must be six characters."),
                  exception.what());
    }

    try {
        TailNumber tail_number ("12345");
    }
    catch (std::out_of_range const &exception) {
        EXPECT_EQ(std::string("Tail Number must be six characters."),
                  exception.what());
    }

    try {
        TailNumber tail_number ("1234567");
    }
    catch (std::out_of_range const &exception) {
        EXPECT_EQ(std::string("Tail Number must be six characters."),
                  exception.what());
    }
}

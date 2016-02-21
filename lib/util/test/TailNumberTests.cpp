/*
 * @file TailNumberTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-9-16
 * @brief Ensures the functionality of TailNumber.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TailNumber.h"

/**
 * Ensures that generated tail numbers are six characters in length.
 */
TEST(TailNumberDefaultConstructor, Length) {
    TailNumber tail_number;
    EXPECT_EQ(6, tail_number.Get().length());
}

/*
 * Test the default tail number constructor by sequentially comparing three new
 * tail numbers to the previously declared tail number. As tail numbers are
 * randomly generated alphanumeric characters, all three comparisons should be
 * inequivalent.
 */
TEST(TailNumberDefaultConstruction, RandomGeneration) {
    TailNumber current_tail_number, last_tail_number;

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_STRNE(last_tail_number.Get().c_str(),
              current_tail_number.Get().c_str());

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_STRNE(last_tail_number.Get().c_str(),
              current_tail_number.Get().c_str());

    last_tail_number = current_tail_number;
    current_tail_number = TailNumber ();
    EXPECT_STRNE(last_tail_number.Get().c_str(),
              current_tail_number.Get().c_str());
}

/*
 * Test the tail number input constructor by evaluating the constructor field
 * assignments.
 */
TEST(TailNumberInputConstructor, Assignment) {
    TailNumber tail_number ("123456");
    EXPECT_STREQ("123456", tail_number.Get().c_str());
}

/**
 * Test the tail number input constructor by ensuring that an exception is
 * thrown when the input string is not six characters.
 */
TEST(TailNumberInputConstructor, OutOfRangeException) {
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

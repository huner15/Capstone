/*
 * TailNumberTests.cpp
 * Specific Atomics
 * Frank Poole
 * 2-8-16
 * VectorTests contains unit tests ensuring the functionality of Vector.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <iostream>

#include "TailNumber.h"

TEST(TailNumber, DefaultConstruction) {
    TailNumber tail_number;
    EXPECT_EQ(6, tail_number.GetTailNumber().length());
    std::cout << tail_number.GetTailNumber() << std::endl;
}

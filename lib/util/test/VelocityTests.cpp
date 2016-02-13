/*
 * @file VelocityTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Ensures the functionality of Velocity.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Velocity.h"

/**
 * Test the Velocity default constructor by ensuring that all velocity axes are
 * initialized to zero.
 */
TEST(VelocityDefaultConstructor, Assignment) {
    Velocity velocity;

    EXPECT_EQ(0, velocity.east);
    EXPECT_EQ(0, velocity.down);
    EXPECT_EQ(0, velocity.north);
}

/**
 * Test the Velocity input constructor by ensuring that velocity axis assignment
 * is valid.
 */
TEST(VelocityInputConstructor, Assignment) {
    Velocity velocity = Velocity (1, 2, 3);

    EXPECT_EQ(1, velocity.east);
    EXPECT_EQ(2, velocity.down);
    EXPECT_EQ(3, velocity.north);
}

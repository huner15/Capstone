/*
 * @file VelocityTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief TODO:Description
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Velocity.h"

TEST(Velocity, Assignment) {
    Velocity velocity;

    EXPECT_EQ(0, velocity.north);
    //EXPECT_EQ(0, velocity.east);
    //EXPECT_EQ(0, velocity.down);
}

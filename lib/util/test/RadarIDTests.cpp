/*
 * @file RadarIDTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Ensures the functionality of RadarID.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "RadarID.h"

/*
 * Test the default radar ID constructor by sequentially comparing three new
 * radar ID's to the previously declared radar ID. As radar IDs are
 * randomly generated numbers, all three comparisons should be
 * inequivalent.
 */
TEST(RadarIDDefaultConstruction, RandomGeneration) {
    RadarID current_radar_id, last_radar_id;

    last_radar_id = current_radar_id;
    current_radar_id = RadarID ();
    EXPECT_NE(last_radar_id.Get(), current_radar_id.Get());

    last_radar_id = current_radar_id;
    current_radar_id = RadarID ();
    EXPECT_NE(last_radar_id.Get(), current_radar_id.Get());

    last_radar_id = current_radar_id;
    current_radar_id = RadarID ();
    EXPECT_NE(last_radar_id.Get(), current_radar_id.Get());
}

/*
 * Test the radar ID input constructor by evaluating the constructor field
 * assignments. Tests that integer overflow behaves as expected.
 */
TEST(RadarIDInputConstructor, Assignment) {
    RadarID radar_id (0);

    EXPECT_EQ(0, radar_id.Get());

    radar_id = RadarID (42);
    EXPECT_EQ(42, radar_id.Get());

    radar_id = RadarID ((uint16_t) (UINT16_MAX + 11));
    EXPECT_EQ(10, radar_id.Get());
}

/*
 * @file VectorTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-8-16
 * @brief VectorTests contains unit tests ensuring the functionality of Vector.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Vector.h"
using namespace Saas_Util;
/*
 * Test 2D vector element accessing by referencing the underlying std::array.
 */
TEST(Vector2D, ArrayReferencing) {
    Vector<double, 2> vector = {0.0, 1.0};
    EXPECT_EQ(2, vector.array.size());
    EXPECT_EQ(0.0, vector.array[0]);
    EXPECT_EQ(1.0, vector.array[1]);
}

/*
 * Test 2D vector element accessing using the field names x and y.
 */
TEST(Vector2D, FieldReferencing) {
    Vector2D vector = {0.0, 1.0};
    EXPECT_EQ(2, vector.array.size());
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(1.0, vector.y);
}

/*
 * Test 2D vector array elements correspond to the field elements x and y
 */
TEST(Vector2D, SharedReferencing) {
    Vector2D vector = {};
    vector.array[0] = 42.0;
    vector.array[1] = 89.0;
    EXPECT_EQ(42.0, vector.x);
    EXPECT_EQ(89.0, vector.y);
}

/*
 * Test 2D vectors initialize to zero when no input is specified.
 */
TEST(Vector2D, ZeroInitialization) {
    Vector2D vector = {};
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(0.0, vector.y);
}

/*
 * Test 3D vector element accessing by referencing the underlying std::array.
 */
TEST(Vector3D, ArrayReferencing) {
    Vector<double, 3> vector = {0.0, 1.0, 2.0};
    EXPECT_EQ(3, vector.array.size());
    EXPECT_EQ(0.0, vector.array[0]);
    EXPECT_EQ(1.0, vector.array[1]);
    EXPECT_EQ(2.0, vector.array[2]);
}

/*
 * Test 3D vector element accessing using the field names x, y, and z.
 */
TEST(Vector3D, FieldReferencing) {
    Vector3D vector = {0.0, 1.0, 2.0};
    EXPECT_EQ(3, vector.array.size());
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(1.0, vector.y);
    EXPECT_EQ(2.0, vector.z);
}

/*
 * Test 3D vector array elements correspond to the field elements x, y, and z
 */
TEST(Vector3D, SharedReferencing) {
    Vector3D vector = {};
    vector.array[0] = 42.0;
    vector.array[1] = 89.0;
    vector.array[2] = -37.5;
    EXPECT_EQ(42.0, vector.x);
    EXPECT_EQ(89.0, vector.y);
    EXPECT_EQ(-37.5, vector.z);
}

/*
 * Test 3D vectors initialize to zero when no input is specified.
 */
TEST(Vector3D, ZeroInitialization) {
    Vector3D vector = {};
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(0.0, vector.y);
    EXPECT_EQ(0.0, vector.z);
}

/*
 * Test 4D vector element accessing by referencing the underlying std::array.
 */
TEST(Vector4D, ArrayReferencing) {
    Vector<double, 4> vector = {0.0, 1.0, 2.0, 3.0};
    EXPECT_EQ(4, vector.array.size());
    EXPECT_EQ(0.0, vector.array[0]);
    EXPECT_EQ(1.0, vector.array[1]);
    EXPECT_EQ(2.0, vector.array[2]);
    EXPECT_EQ(3.0, vector.array[3]);
}

/* Test 4D vector element accessing using the field names x, y, z, and w. */
TEST(Vector4D, FieldReferencing) {
    Vector4D vector = {0.0, 1.0, 2.0, 3.0};
    EXPECT_EQ(4, vector.array.size());
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(1.0, vector.y);
    EXPECT_EQ(2.0, vector.z);
    EXPECT_EQ(3.0, vector.w);
}

/*
 * Test 4D vector array elements correspond to the field elements x, y, z, and
 * w.
 */
TEST(Vector4D, SharedReferencing) {
    Vector4D vector = {};
    vector.array[0] = 42.0;
    vector.array[1] = 89.0;
    vector.array[2] = -37.5;
    vector.array[3] = -7.0;
    EXPECT_EQ(42.0, vector.x);
    EXPECT_EQ(89.0, vector.y);
    EXPECT_EQ(-37.5, vector.z);
    EXPECT_EQ(-7.0, vector.w);
}

/*
 * Test 4D vectors initialize to zero when no input is specified.
 * */
TEST(Vector4D, ZeroInitialization) {
    Vector4D vector = {};
    EXPECT_EQ(0.0, vector.x);
    EXPECT_EQ(0.0, vector.y);
    EXPECT_EQ(0.0, vector.z);
    EXPECT_EQ(0.0, vector.w);
}

/*
 * SpecialMathTests.cpp
 * Specific Atomics
 * Michael Lenz
 * 2-15-16
 * Tests Special math
*/
#include <gtest/gtest.h>
#include "SpecialMath.h"


TEST(DistanceFormula, Everything)
{
    using namespace Saas_Util;{
    //TODO fix whatever is going on here
    Vector<double, 2> a;
    a.x = 0;
    a.y = 0;
    Vector<double, 2> b;
    b.x = 0;
    b.y = 5;
//    double result = SpecialMath::DistanceFormula<double, 2>(a, b);
  //  EXPECT_EQ(5, result);
   // result = SpecialMath::DistanceFormula<double, 2>(b, a);
  //  EXPECT_EQ(5, result);
    b.x = 5;
  //  EXPECT_EQ(sqrt(50), (SpecialMath::DistanceFormula<double, 2>(a, b)));
  //  EXPECT_EQ(sqrt(50), (SpecialMath::DistanceFormula<double, 2>(b, a)));
    Vector<double, 3> c;
    c.x = 0;
    c.y = 0;
    c.z = 0;
    Vector<double, 3> d;
    d.y = 5;
 //   EXPECT_EQ(5, (SpecialMath::DistanceFormula<double, 3>(c, d)));
  //  EXPECT_EQ(5, (SpecialMath::DistanceFormula<double, 3>(d, c)));
    d.x = 5;
  //  EXPECT_EQ(sqrt(50), (SpecialMath::DistanceFormula<double, 3>(c, d)));
 //   EXPECT_EQ(sqrt(50), (SpecialMath::DistanceFormula<double, 3>(d, c)));
    d.z = 5;
 //   EXPECT_EQ(sqrt(75), (SpecialMath::DistanceFormula<double, 3>(c, d)));
 //   EXPECT_EQ(sqrt(75), (SpecialMath::DistanceFormula<double, 3>(d, c)));
    };
}

TEST(LineDistance, Everything) {
    using namespace Saas_Util; {
        Vector<double, 3> a;
        a.x = 0;
        a.y = 1;
        a.z = 0;
        Vector<double, 3> b;
        b.x = 1;
        b.y = 0;
        b.z = 0;
        Vector<double, 3> c;
        c.x = 0;
        c.y = 0;
        c.z = 0;
        EXPECT_EQ(1, SpecialMath::LineDistance(a, b, c));
        a.x = 1;
        a.y = 1;
        EXPECT_EQ(sqrt(2), SpecialMath::LineDistance(a, b, c));
        b.x = -1;
        EXPECT_EQ(1, SpecialMath::LineDistance(a, b, c));
        b.y = -1;
        EXPECT_EQ(0, SpecialMath::LineDistance(a, b, c));
    }
}
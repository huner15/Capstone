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
   // double result = SpecialMath::DistanceFormula<double, 2>(a, b);
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
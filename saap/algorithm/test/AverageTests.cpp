
#include <gtest/gtest.h>
#include <GeographicCoordinate.h>
#include <SphericalCoordinate.h>
#include <Velocity.h>
#include <EmptySphericalCoordinate.h>

//Velocity Tests
TEST(Velocity, allValues) {
    Velocity *one = new Velocity(1, 3, 4); //same v values
    Velocity *two = new Velocity(3, 4, 1);
    Velocity *three = new Velocity(4, 1, 3);

    Velocity result = Velocity::Average(one, two, three);
    EXPECT_EQ(2, result.East());
    EXPECT_EQ(2, result.Down());
    EXPECT_EQ(2, result.North());
}

TEST(Velocity, oneNull) {
    Velocity *one = NULL;
    Velocity *two = new Velocity(9, 16, 9);
    Velocity *three = new Velocity(16, 9, 16);

    Velocity result = Velocity::Average(one, two, three);
    EXPECT_EQ(5, result.East());
    EXPECT_EQ(5, result.Down());
    EXPECT_EQ(5, result.North());

    result = Velocity::Average(two, three, one);
    EXPECT_EQ(5, result.East());
    EXPECT_EQ(5, result.Down());
    EXPECT_EQ(5, result.North());

    result = Velocity::Average(two, one, three);
    EXPECT_EQ(5, result.East());
    EXPECT_EQ(5, result.Down());
    EXPECT_EQ(5, result.North());
}

TEST(Velocity, twoNull) {
    Velocity *one = NULL;
    Velocity *two = new Velocity(1, 2, 3);

    Velocity result = Velocity::Average(one, two, one);
    EXPECT_EQ(1, result.East());
    EXPECT_EQ(2, result.Down());
    EXPECT_EQ(3, result.North());

    result = Velocity::Average(two, one, one);
    EXPECT_EQ(1, result.East());
    EXPECT_EQ(2, result.Down());
    EXPECT_EQ(3, result.North());

    result = Velocity::Average(one, one, two);
    EXPECT_EQ(1, result.East());
    EXPECT_EQ(2, result.Down());
    EXPECT_EQ(3, result.North());
}

TEST(Velocity, threeNull) {
    Velocity *one = NULL;
    Velocity *two = NULL;
    Velocity *three = NULL;

    Velocity result = Velocity::Average(one, two, three);

    EXPECT_EQ(0, result.East());
    EXPECT_EQ(0, result.Down());
    EXPECT_EQ(0, result.North());
}

TEST(Velocity, outlier) {
    Velocity *one = new Velocity(1, 2, 1); //vOne = 1.817
    Velocity *two = new Velocity(9, 16, 9); //vTwo = 7.477
    Velocity *three = new Velocity(16, 9, 16); //vThree = 8.4014

    Velocity result = Velocity::Average(one, two, three);
    EXPECT_EQ(5, result.East());
    EXPECT_EQ(5, result.Down());
    EXPECT_EQ(5, result.North());
}

TEST(SphericalCoordinate, allValues) {
    SphericalCoordinate *one = new SphericalCoordinate(1, 3, 4); //same v values
    SphericalCoordinate *two = new SphericalCoordinate(3, 4, 1);
    SphericalCoordinate *three = new SphericalCoordinate(4, 1, 3);

    SphericalCoordinate result = SphericalCoordinate::Average(one, two, three);
    EXPECT_EQ(2, result.GetRange());
    EXPECT_EQ(2, result.GetElevation());
    EXPECT_EQ(2, result.GetAzimuth());
}

TEST(SphericalCoordinate, oneNull) {
    SphericalCoordinate *one = NULL;
    SphericalCoordinate *two = new SphericalCoordinate(9, 16, 9);
    SphericalCoordinate *three = new SphericalCoordinate(16, 9, 16);

    SphericalCoordinate result = SphericalCoordinate::Average(one, two, three);
    EXPECT_EQ(5, result.GetRange());
    EXPECT_EQ(5, result.GetElevation());
    EXPECT_EQ(5, result.GetAzimuth());

    result = SphericalCoordinate::Average(two, three, one);
    EXPECT_EQ(5, result.GetRange());
    EXPECT_EQ(5, result.GetElevation());
    EXPECT_EQ(5, result.GetAzimuth());

    result = SphericalCoordinate::Average(two, one, three);
    EXPECT_EQ(5, result.GetRange());
    EXPECT_EQ(5, result.GetElevation());
    EXPECT_EQ(5, result.GetAzimuth());
}

TEST(SphericalCoordinate, twoNull) {
    SphericalCoordinate *one = NULL;
    SphericalCoordinate *two = new SphericalCoordinate(1, 2, 3);

    SphericalCoordinate result = SphericalCoordinate::Average(one, two, one);
    EXPECT_EQ(1, result.GetRange());
    EXPECT_EQ(2, result.GetElevation());
    EXPECT_EQ(3, result.GetAzimuth());

    result = SphericalCoordinate::Average(two, one, one);
    EXPECT_EQ(1, result.GetRange());
    EXPECT_EQ(2, result.GetElevation());
    EXPECT_EQ(3, result.GetAzimuth());

    result = SphericalCoordinate::Average(one, one, two);
    EXPECT_EQ(1, result.GetRange());
    EXPECT_EQ(2, result.GetElevation());
    EXPECT_EQ(3, result.GetAzimuth());
}

TEST(SphericalCoordinate, threeNull) {
    SphericalCoordinate *one = NULL;
    SphericalCoordinate *two = NULL;
    SphericalCoordinate *three = NULL;

    SphericalCoordinate result = SphericalCoordinate::Average(one, two, three);

    EXPECT_EQ(0, result.GetRange());
    EXPECT_EQ(0, result.GetElevation());
    EXPECT_EQ(0, result.GetAzimuth());
}

TEST(SphericalCoordinate, outlier) {
    //vOne = 1.817
    SphericalCoordinate *one = new SphericalCoordinate(1, 2, 1);
    //vTwo = 7.477
    SphericalCoordinate *two = new SphericalCoordinate(9, 16, 9);
    //vThree = 8.4014
    SphericalCoordinate *three = new SphericalCoordinate(16, 9, 16);

    SphericalCoordinate result = SphericalCoordinate::Average(one, two, three);
    EXPECT_EQ(5, result.GetRange());
    EXPECT_EQ(5, result.GetElevation());
    EXPECT_EQ(5, result.GetAzimuth());
}

//GeographicCoordinate Tests
TEST(GeographicCooridinate, allValues) {
    //same v values
    GeographicCoordinate *one = new GeographicCoordinate(1, 3, 4);
    GeographicCoordinate *two = new GeographicCoordinate(3, 4, 1);
    GeographicCoordinate *three = new GeographicCoordinate(4, 1, 3);

    GeographicCoordinate result =
            GeographicCoordinate::Average(one, two, three);
    EXPECT_EQ(2, result.GetLatitude());
    EXPECT_EQ(2, result.GetLongitude());
    EXPECT_EQ(2, result.GetAltitude());
}

TEST(GeographicCoordinate, oneNull) {
    GeographicCoordinate *one = NULL;
    GeographicCoordinate *two = new GeographicCoordinate(9, 16, 9);
    GeographicCoordinate *three = new GeographicCoordinate(16, 9, 16);

    GeographicCoordinate result =
            GeographicCoordinate::Average(one, two, three);
    EXPECT_EQ(5, result.GetLatitude());
    EXPECT_EQ(5, result.GetLongitude());
    EXPECT_EQ(5, result.GetAltitude());

    result = GeographicCoordinate::Average(two, three, one);
    EXPECT_EQ(5, result.GetLatitude());
    EXPECT_EQ(5, result.GetLongitude());
    EXPECT_EQ(5, result.GetAltitude());

    result = GeographicCoordinate::Average(two, one, three);
    EXPECT_EQ(5, result.GetLatitude());
    EXPECT_EQ(5, result.GetLongitude());
    EXPECT_EQ(5, result.GetAltitude());
}

TEST(GeographicCoordinate, twoNull) {
    GeographicCoordinate *one = NULL;
    GeographicCoordinate *two = new GeographicCoordinate(1, 2, 3);

    GeographicCoordinate result =
            GeographicCoordinate::Average(one, two, one);
    EXPECT_EQ(1, result.GetLatitude());
    EXPECT_EQ(2, result.GetLongitude());
    EXPECT_EQ(3, result.GetAltitude());

    result = GeographicCoordinate::Average(two, one, one);
    EXPECT_EQ(1, result.GetLatitude());
    EXPECT_EQ(2, result.GetLongitude());
    EXPECT_EQ(3, result.GetAltitude());

    result = GeographicCoordinate::Average(one, one, two);
    EXPECT_EQ(1, result.GetLatitude());
    EXPECT_EQ(2, result.GetLongitude());
    EXPECT_EQ(3, result.GetAltitude());
}

TEST(GeographicCoordinate, threeNull) {
    GeographicCoordinate *one = NULL;
    GeographicCoordinate *two = NULL;
    GeographicCoordinate *three = NULL;

    GeographicCoordinate result =
            GeographicCoordinate::Average(one, two, three);

    EXPECT_EQ(0, result.GetLatitude());
    EXPECT_EQ(0, result.GetLongitude());
    EXPECT_EQ(0, result.GetAltitude());
}

TEST(GeographicCoordinate, outlier) {
    //vOne = 1.817
    GeographicCoordinate *one = new GeographicCoordinate(1, 2, 1);
    //vTwo = 7.477
    GeographicCoordinate *two = new GeographicCoordinate(9, 16, 9);
    //vThree = 8.4014
    GeographicCoordinate *three = new GeographicCoordinate(16, 9, 16);

    GeographicCoordinate result =
            GeographicCoordinate::Average(one, two, three);
    EXPECT_EQ(5, result.GetLatitude());
    EXPECT_EQ(5, result.GetLongitude());
    EXPECT_EQ(5, result.GetAltitude());
}
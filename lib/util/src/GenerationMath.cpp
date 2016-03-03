/*
 * @file GenerationMath.cpp
 * @author Specific Atomics
 * @authors Kevin Pham
 * @date 2/26/2016
 * @brief TODO: Description
 */

#include <GeographicCoordinate.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "GenerationMath.h"

#define EARTH_RAD2 20903520.0
#define EARTH_RAD 3961.0
#define PI 3.14159265359

double GenerationMath::DistanceBetweenTwoCoordinates(
        GeographicCoordinate coord1, GeographicCoordinate coord2) {
    //a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
    //c = 2 ⋅ atan2( √a, √(1−a) )
    //d = R ⋅ c
    double lat1 = ToRadians(coord1.GetLatitude());
    double lat2 = ToRadians(coord2.GetLatitude());
    double d_lat = ToRadians(coord2.GetLatitude() - coord1.GetLatitude());
    double d_long = ToRadians(coord2.GetLongitude() - coord1.GetLongitude());

    double a = sin(d_lat/2) * sin(d_lat/2) + cos(lat1) * cos(lat2) *
            sin(d_long/2) * sin(d_long/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    //std::cout << "c: " << c << std::endl;
    //std::cout << "Result: " << (20,903,520 * c) << std::endl;
    return EARTH_RAD * c * 5280;
}

double GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
        GeographicCoordinate coord1, GeographicCoordinate coord2) {

   /* var y = Math.sin(λ2-λ1) * Math.cos(φ2);
    var x = Math.cos(φ1)*Math.sin(φ2) -
            Math.sin(φ1)*Math.cos(φ2)*Math.cos(λ2-λ1);
    var brng = Math.atan2(y, x).toDegrees();

    θ = atan2( sin Δλ ⋅ cos φ2 , cos φ1 ⋅ sin φ2 − sin φ1 ⋅ cos φ2 ⋅ cos Δλ )*/
    double lat1 = ToRadians(coord1.GetLatitude());
    double lat2 = ToRadians(coord2.GetLatitude());
    double long1 = ToRadians(coord1.GetLongitude());
    double long2 = ToRadians(coord2.GetLongitude());


    double y = sin(long2-long1) * cos(lat2);
    double x = cos(lat1) * sin(lat2) -
            sin(lat1) * cos(lat2) * cos(long2 - long1);
    //return ToDegrees(atan2(y, x));
    return fmod(ToDegrees(atan2(y, x)) + 360, 360.0);
}

GeographicCoordinate GenerationMath::DestinationPoint(
        GeographicCoordinate start, Velocity velocity, double current_bearing) {
    //φ2 = asin( sin φ1 ⋅ cos δ + cos φ1 ⋅ sin δ ⋅ cos θ )
    //λ2 = λ1 + atan2( sin θ ⋅ sin δ ⋅ cos φ1, cos δ − sin φ1 ⋅ sin φ2 )

    double distance = sqrt(velocity.east * velocity.east +
                                   velocity.north * velocity.north);

    double start_lat = ToRadians(start.GetLatitude());
    double start_long = ToRadians(start.GetLongitude());
    double angular_dist = (distance / EARTH_RAD2);

    double dest_lat = asin( sin(start_lat) * cos(angular_dist) +
                                 cos(start_lat) * sin(angular_dist)
                                 * cos(ToRadians(current_bearing)));

    double dest_long = start_long
                       + atan2(sin(ToRadians(current_bearing)) * sin(angular_dist)
                               * cos(start_lat),
                               cos(angular_dist) -
                                       sin(start_lat) * sin(dest_lat));
    dest_lat = ToDegrees(dest_lat);
    dest_long = ToDegrees(dest_long);
    return GeographicCoordinate (dest_lat, dest_long,
                                 start.GetAltitude()-velocity.down);
}

double GenerationMath::ToRadians(double degrees) {
    return (degrees * M_PI / 180.0);
}

double GenerationMath::ToDegrees(double radians) {
    std::cout << "radians: " << radians << " degrees: " << std::defaultfloat << std::setprecision(10) << (radians * 180.0 / PI) << std::endl;
    return radians * 180.0 / M_PI;
}
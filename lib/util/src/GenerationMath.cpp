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
#include "GenerationMath.h"

//#define EARTH_RAD 20,903,520
#define EARTH_RAD 3961

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

double GenerationMath::ToRadians(double degrees) {
    return (degrees * M_PI / 180.0);
}
/*
 * @file GenerationMath.h
 * @author Specific Atomics
 * @authors Kevin Pham
 * @date 2/26/2016
 * @brief TODO: Description
 */

#ifndef GENERATIONMATH_H_
#define GENERATIONMATH_H_

#include "GeographicCoordinate.h"
#include "Velocity.h"

class GenerationMath {
private:

public:

    /*
     * Finds the absolute distance between two sets of coordinates in feet.
     * @param coord1 is a GeographicCoordinate that you want to find the distance from.
     * @param coord2 is a GeographicCOordinate that you want to find the distance to.
     * @return a double representing the distance in feet.
     */
    static double DistanceBetweenTwoCoordinates(GeographicCoordinate coord1,
        GeographicCoordinate coord2);

    /*
     * Converts a radian to degrees.
     * @param degrees is a double value that is converted to radians.
     * @return a double representing the parameter in radians.
     */
    static double ToRadians(double degrees);

    /**
     * Converts a radian to degrees
     * @param radians is a double value that is to be converted to degrees.
     * @return a double representing the parameter in degrees.
     */
    static double ToDegrees(double radians);

    /**
     * Finds the absolute bearing between two Geographic Coordinates.
     * @param coord1 is the GeographicCoordinate of the initial position.
     * @param coord2 is the GeographicCOordinate of the destination.
     * @return double value that is the absolute bearing between the two points.
     */
    static double AbsoluteBearingBetweenTwoCoordinates(
            GeographicCoordinate coord1, GeographicCoordinate coord2);

    /**
     * Calculates the destination of an aircraft.
     * @param start is the initial position
     * @param velocity is the velocity that the object is traveling
     * @param current_bearing is the objects current bearing.
     * @return The GeographicCoordinate that the object ends at.
     */
    static GeographicCoordinate DestinationPoint(
            GeographicCoordinate start,
            Velocity velocity, double current_bearing);

    /**
     * Converts feet to nautical miles.
     * @param the length in feet
     * @return the feet value converted to nautical miles.
     */
    static double FeetToNauticalMiles(double feet);


};

#endif

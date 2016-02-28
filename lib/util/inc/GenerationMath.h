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

class GenerationMath {
private:

public:

    static double DistanceBetweenTwoCoordinates(GeographicCoordinate coord1,
        GeographicCoordinate coord2);

    static double ToRadians(double degrees);



};

#endif //SAAS_GENERATIONMATH_H

/*
 * SphericalCoordinate.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef SPHERICAL_COORDINATE_H_
#define SPHERICAL_COORDINATE_H_

#include "Vector.h"

class SphericalCoordinate {
private:
    double _range;
    double _elevation;
    double _azimuth;

public:
    SphericalCoordinate() {};
    SphericalCoordinate(double range, double elevation, double azimuth);

    ~SphericalCoordinate();
};

#endif

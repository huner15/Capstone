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
    double _bearing;

public:
    SphericalCoordinate() {};
    SphericalCoordinate(double range, double elevation, double azimuth,
                        double bearing);

    ~SphericalCoordinate();

    /**
     * Accessor for the Range of the Spherical Coordinate.
     * @return range of the spherical coordinate.
     */
    double GetRange();

    /**
     * Accessor for the Elevation of the Spherical Coordinate.
     * @return Elevation of the spherical coordinate.
     */
    double GetElevation();

    /**
     * Accessor for the Azimuth of the Spherical Coordinate.
     * @return azimuth of the spherical coordinate.
     */
    double GetAzimuth();

    /**
     * Accessor for the Bearing of the Spherical Coordinate.
     * @return bearing of the spherical coordinate.
     */
    double GetBearing();
};

#endif

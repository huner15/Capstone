/*
 * SphericalCoordinate.cpp
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#include "SphericalCoordinate.h"

SphericalCoordinate::SphericalCoordinate(
        double range, double elevation,double azimuth) {
    _range = range;
    _elevation = elevation;
    _azimuth = azimuth;
}

SphericalCoordinate::~SphericalCoordinate() {

}

double SphericalCoordinate::GetRange() {
    return _range;
}

double SphericalCoordinate::GetElevation() {
    return _elevation;
}

double SphericalCoordinate::GetAzimuth() {
    return _azimuth;
}

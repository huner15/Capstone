/*
 * SphericalCoordinate.cpp
 * Specific Atomics
 * Frank Poole, Dat Tran
 * 2-13-16
 * TODO: Description
 */

#include "SphericalCoordinate.h"

SphericalCoordinate::SphericalCoordinate(
        double range, double elevation, double azimuth) {
    _range = range;
    _elevation = elevation;
    _azimuth = azimuth;
}

SphericalCoordinate::~SphericalCoordinate() {
}

double SphericalCoordinate::GetRange() const {
    return _range;
}

double SphericalCoordinate::GetElevation() const {
    return _elevation;
}

double SphericalCoordinate::GetAzimuth() const {
    return _azimuth;
}

// TODO: Update to return a calulated bearing from azimuth.
double SphericalCoordinate::GetBearing() const {
    return _azimuth;
}

Saas_Util::Vector<double, 3> SphericalCoordinate::ToCartesianCoordinates() {
    Saas_Util::Vector<double, 3> cartesian;
    cartesian.x = _range * sin(_elevation) * cos(_azimuth);
    cartesian.y = _range * sin(_elevation) * sin(_azimuth);
    cartesian.z = _range * cos(_elevation);
    return cartesian;
}

// TODO: Implement GetBearing (using existing data, do not add a bearing
// member).

double SphericalCoordinate::operator-(const SphericalCoordinate &other) {
    return sqrt(pow(this->GetRange(), 2) + pow(other.GetRange(), 2) -
                2 * this->GetRange() * other.GetRange() *
                (sin(this->GetElevation()) * sin(other.GetElevation() *
                                                 cos(this->GetAzimuth() -
                                                     other.GetAzimuth()) +
                                                 cos(this->GetElevation()) *
                                                 cos(other.GetElevation()))));
}

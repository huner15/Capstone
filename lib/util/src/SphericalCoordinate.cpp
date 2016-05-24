/*
 * SphericalCoordinate.cpp
 * Specific Atomics
 * Frank Poole, Dat Tran, Andrea Savage
 * 3-6-16
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

// TODO: Update to return a calculated bearing from azimuth.
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

SphericalCoordinate SphericalCoordinate:: Average(SphericalCoordinate
    *one, SphericalCoordinate *two, SphericalCoordinate *three) {
    double range = 0, elevation = 0, azimuth = 0, count = 0;
    double vOne, vTwo, vThree, removeVal;
    std::vector<SphericalCoordinate *> coords;

    if (one != NULL) {
        count++;
        coords.push_back(one);
    }
    if (two != NULL) {
        count++;
        coords.push_back(two);
    }
    if (three != NULL) {
        count++;
        coords.push_back(three);
    }

    for (uint i = 0; i < count; i++)
    {
        range += coords.at(i)->_range;
        elevation += coords.at(i)->_elevation;
        azimuth += coords.at(i)->_azimuth;
    }

    //Remove outlier if have all three coordinates and it exists
    if (count == 3) {
        vOne = cbrt(pow(coords.at(0)->_range, 2) +
            pow(coords.at(0)->_elevation, 2) + pow(coords.at(0)->_azimuth, 2));
        vTwo = cbrt(pow(coords.at(1)->_range, 2) +
            pow(coords.at(1)->_elevation, 2) + pow(coords.at(1)->_azimuth, 2));
        vThree = cbrt(pow(coords.at(2)->_range, 2) +
            pow(coords.at(2)->_elevation, 2) + pow(coords.at(2)->_azimuth, 2));

        //if difference is twice as big as other distance, must be an outlier
        removeVal = (fabs(vOne - vTwo) >= 2 * fabs(vTwo - vThree)) ? 1 : 0;
        removeVal += (fabs(vTwo - vThree) >= 2 * fabs(vThree - vOne)) ? 2 : 0;
        removeVal += (fabs(vThree - vOne) >= 2 * fabs(vOne - vTwo)) ? 3 : 0;

        if (removeVal != 0) {
            count--;
            range -= coords.at(removeVal - 1)->_range;
            elevation -= coords.at(removeVal - 1)->_elevation;
            azimuth -= coords.at(removeVal - 1)->_azimuth;
        }
    }

    //No coordinates exist
    if (count == 0)
    {
        return SphericalCoordinate(0, 0, 0);
    }

    //geometric mean
    range = pow(range, 1 / count);
    elevation = pow(elevation, 1 / count);
    azimuth = pow(azimuth, 1 / count);

    return SphericalCoordinate(range, elevation, azimuth);
}

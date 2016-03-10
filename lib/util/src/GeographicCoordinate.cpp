/*
 * GeographicCoordinate.cpp
 * Specific Atomics
 * Frank Poole, Kevin Pham, Andrea Savage
 * 3-6-16
 * TODO: Description
 */

#include <stdexcept>
#include "GeographicCoordinate.h"

GeographicCoordinate::GeographicCoordinate(
        double latitude, double longitude, double altitude) {
    if(latitude <= 90 && latitude >= -90 &&
            longitude <= 180 && longitude >= -180 && altitude >= -50000) {
        _latitude = latitude;
        _longitude = longitude;
        _altitude = altitude;
    }
    else {
        throw std::domain_error ("Value not in domain.");
    }
}

double GeographicCoordinate::GetLatitude() const {
    return _latitude;
}

double GeographicCoordinate::GetLongitude() const {
    return _longitude;
}

double GeographicCoordinate::GetAltitude() const {
    return _altitude;
}

bool GeographicCoordinate::operator==(GeographicCoordinate coord) {
    return (coord.GetLatitude() == _latitude
        && coord.GetLongitude() == _longitude
        && coord.GetAltitude() == _altitude);
}

GeographicCoordinate::~GeographicCoordinate() {

}

GeographicCoordinate *GeographicCoordinate::Average(GeographicCoordinate
    *one, GeographicCoordinate *two, GeographicCoordinate *three) {
    double latitude = 0, longitude = 0, altitude = 0, count = 0;
    double vOne, vTwo, vThree, removeVal;
    std::vector<GeographicCoordinate *> coords;

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

    for (int i = 0; i < coords.size(); i++)
    {
        latitude += coords.at(i)->_latitude;
        longitude += coords.at(i)->_longitude;
        altitude += coords.at(i)->_altitude;
    }

    //Remove outlier if have all three coordinates and it exists
    if (count == 3) {
        vOne = cbrt(pow(coords.at(0)->_latitude, 2) +
            pow(coords.at(0)->_longitude, 2) + pow(coords.at(0)->_altitude, 2));
        vTwo = cbrt(pow(coords.at(1)->_latitude, 2) +
            pow(coords.at(1)->_longitude, 2) + pow(coords.at(1)->_altitude, 2));
        vThree = cbrt(pow(coords.at(2)->_latitude, 2) +
            pow(coords.at(2)->_longitude, 2) + pow(coords.at(2)->_altitude, 2));

        //if difference is twice as big as other distance, must be an outlier
        removeVal = (fabs(vOne - vTwo) >= 2 * fabs(vTwo - vThree)) ? 0 : 0;
        removeVal = (fabs(vTwo - vThree) >= 2 * fabs(vThree - vOne)) ? 1 : 0;
        removeVal = (fabs(vThree - vOne) >= 2 * fabs(vOne - vTwo)) ? 2 : 0;

        if (removeVal != 0) {
            count--;
            latitude -= coords.at(removeVal)->_latitude;
            longitude -= coords.at(removeVal)->_longitude;
            altitude -= coords.at(removeVal)->_altitude;
        }
    }

    //No coordinates exist
    if (count == 0)
    {
        return NULL;
    }

    //geometric mean
    latitude = pow(latitude, 1 / count);
    longitude = pow(longitude, 1 / count);
    altitude = pow(altitude, 1 / count);

    return new GeographicCoordinate(latitude, longitude, altitude);
}

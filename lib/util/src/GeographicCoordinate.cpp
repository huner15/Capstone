/*
 * GeographicCoordinate.cpp
 * Specific Atomics
 * Frank Poole, Kevin Pham
 * 2-9-16
 * TODO: Description
 */

#include <stdexcept>
#include "GeographicCoordinate.h"

GeographicCoordinate::GeographicCoordinate(
        double latitude, double longitude, double altitude) {
    if(latitude <= 180 && latitude >= -180 &&
            longitude <= 180 && longitude >= -180 && altitude > 0 ) {
        _latitude = latitude;
        _longitude = longitude;
        _altitude = altitude;
    }
    else {
        throw std::domain_error ("Value not in domain.");
    }
}

double GeographicCoordinate::GetLatitude() {
    return _latitude;
}

double GeographicCoordinate::GetLongitude() {
    return _longitude;
}

double GeographicCoordinate::GetAltitude() {
    return _altitude;
}

GeographicCoordinate::~GeographicCoordinate() {

}

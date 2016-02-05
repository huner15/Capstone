/*
 * GeographicCoordinate.cpp
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#include "GeographicCoordinate.h"

GeographicCoordinate::GeographicCoordinate(
        double latitude, double longitude, double altitude) {
    _latitude = latitude;
    _longitude = longitude;
    _altitude = altitude;
}

GeographicCoordinate::~GeographicCoordinate() {

}

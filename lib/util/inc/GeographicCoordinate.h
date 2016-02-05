/*
 * GeographicCoordinate.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef GEOGRAPHIC_COORDINATE_H_
#define GEOGRAPHIC_COORDINATE_H_

class GeographicCoordinate {
private:
    /** The latitude of a geographic coordinate (+-180 degrees). */
    double _latitude;

    /** The longitude of a geographic coordinate (+-180 degrees). */
    double _longitude;

    /** The altitude of a geographic coordinate. */
    double _altitude;

public:
    GeographicCoordinate(double latitude, double longitude, double altitude);

    ~GeographicCoordinate();
};

#endif

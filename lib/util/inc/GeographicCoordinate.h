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
    GeographicCoordinate() {};
    GeographicCoordinate(double latitude, double longitude, double altitude);

    /**
     * Accessor for the Latitude of the Geographic Coordinate.
     * @return latitude of the geographic coordinate.
     */
    double GetLatitude() const;

    /**
     * Accessor for the Longitude of the Geographic Coordinate.
     * @return longitude of the geographic coordinate.
     */
    double GetLongitude() const;

    /**
     * Accessor for the altitude of the Geographic Coordinate.
     * @return altitude of the geographic coordinate.
     */
    double GetAltitude() const;

    /**
     * Checks to see if two GeographicCoordinates are the same;
     * @return bool stating whether the two GeographicCoordinates are the same.
     */
    bool operator==(GeographicCoordinate coord);

    ~GeographicCoordinate();
};

#endif

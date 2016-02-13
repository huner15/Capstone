/*
 * FlightReport.cpp
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#include "FlightReport.h"

//This is causing an error, something with implicit construction...
FlightReport::FlightReport(std::time_t time, TailNumber tail_number, TcasID tcas_id,
RadarID radar_id, GeographicCoordinate geographic_coordinate,
SphericalCoordinate spherical_coordinate, Vector3D velocity) {
    _time = time;
    _tail_number = tail_number;
    _tcas_id = tcas_id;
    _radar_id = radar_id;
    _geographic_coordinate = geographic_coordinate;
    _spherical_coordinate = spherical_coordinate;
    _velocity = velocity;
}


FlightReport::~FlightReport() {

}

OwnshipReport FlightReport::createOwnshipReport() {
    OwnshipReport ownshipReport;
    ownshipReport.set_timestamp(_time);
    ownshipReport.set_ownship_latitude(_geographic_coordinate.GetLatitude());
    ownshipReport.set_ownship_longitude(_geographic_coordinate.GetLongitude());
    ownshipReport.set_ownship_altitude(_geographic_coordinate.GetAltitude());
    ownshipReport.set_north(4);
    ownshipReport.set_east(5);
    ownshipReport.set_down(6);
}

AdsBReport FlightReport::createAdsBReport() {
    AdsBReport adsBReport;

    adsBReport.set_timestamp(_time);
    adsBReport.set_latitude(_geographic_coordinate.GetLatitude());
    adsBReport.set_longitude(_geographic_coordinate.GetLongitude());
    adsBReport.set_altitude(_geographic_coordinate.GetAltitude());
    adsBReport.set_tail_number(_tail_number);
    adsBReport.set_north(12);
    adsBReport.set_east(13);
    adsBReport.set_down(14);

}

RadarReport FlightReport::createRadarReport() {
    RadarReport radarReport;

    radarReport.set_timestamp(_time);
    radarReport.set_range(_spherical_coordinate.GetRange());
    radarReport.set_azimuth(_spherical_coordinate.GetAzimuth());
    radarReport.set_elevation(_spherical_coordinate.GetElevation());
    radarReport.set_id(_radar_id);
    radarReport.set_north(20);
    radarReport.set_east(21);
    radarReport.set_down(22);
    radarReport.set_latitude(_geographic_coordinate.GetLatitude());
    radarReport.set_longitude(_geographic_coordinate.GetLongitude());
    radarReport.set_altitude(_geographic_coordinate.GetAltitude());
}

TcasReport FlightReport::createTcasReport() {
    TcasReport tcasReport;

    tcasReport.set_id(_tcas_id);
    tcasReport.set_range(_spherical_coordinate.GetRange());
    tcasReport.set_altitude(_geographic_coordinate.GetAltitude());
    tcasReport.set_bearing(29);
}

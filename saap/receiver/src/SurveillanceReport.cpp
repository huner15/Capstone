/**
* @file SurveillanceReport.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief Constructs a SurveillanceReport and converts a Cluster into one
 * most likely SurveillanceReport.
*/

#include "SurveillanceReport.h"

SurveillanceReport::SurveillanceReport() {

}

SurveillanceReport::SurveillanceReport(std::time_t time, TailNumber
    tail_number, TcasID tcas_id, RadarID radar_id, GeographicCoordinate
    geographic_coordinate, SphericalCoordinate spherical_coordinate, Velocity
    velocity, Device type) {
    _time = time;
    _tail_number = tail_number;
    _tcas_id = tcas_id;
    _radar_id = radar_id;
    _geographic_coordinate = geographic_coordinate;
    _spherical_coordinate = spherical_coordinate;
    _velocity = velocity;
    _type = type;
}

std::time_t SurveillanceReport::GetTime() {
    return _time;
}

Device SurveillanceReport::GetDevice() {
    return _type;
}

GeographicCoordinate *SurveillanceReport::GetGeographicCoordinate() {
    return &_geographic_coordinate;
}

RadarID SurveillanceReport::GetRadarID() {
    return _radar_id;
}

SphericalCoordinate *SurveillanceReport::GetSphericalCoordinate() {
    return &_spherical_coordinate;
}

void SurveillanceReport::SetSphericalCoordinate(SphericalCoordinate coord) {
    _spherical_coordinate = coord;
}

TailNumber SurveillanceReport::GetTailNumber() {
    return _tail_number;
}

Velocity *SurveillanceReport::GetVelocity() {
    return &_velocity;
}

TcasID SurveillanceReport::GetTcasID() {
    return _tcas_id;
}

double SurveillanceReport::GetRange() const {
    return _spherical_coordinate.GetRange();
}

double SurveillanceReport::GetElevation() const {
    return _spherical_coordinate.GetElevation();
}

double SurveillanceReport::GetAzimuth() const {
    return _spherical_coordinate.GetAzimuth();
}

double SurveillanceReport::GetLatitude() const {
    return _geographic_coordinate.GetLatitude();
}

double SurveillanceReport::GetLongitude() const {
    return _geographic_coordinate.GetLongitude();
}

double SurveillanceReport::GetAltitude() const {
    return _geographic_coordinate.GetAltitude();
}

double SurveillanceReport::GetBearing() const {
    return _spherical_coordinate.GetBearing();
}
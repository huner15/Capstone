/*
 * FlightReport.cpp
 * Specific Atomics
 * Frank Poole, Dat Tran
 * 2-4-16
 * TODO: Description
 */

#include <cdti.pb.h>
#include <iostream>
#include "FlightReport.h"

//This is causing an error, something with implicit construction...
FlightReport::FlightReport(std::time_t time, TailNumber tail_number, TcasID tcas_id,
RadarID radar_id, GeographicCoordinate geographic_coordinate,
SphericalCoordinate spherical_coordinate, Velocity velocity, Device type) {
    _time = time;
    _tail_number = tail_number;
    _tcas_id = tcas_id;
    _radar_id = radar_id;
    _geographic_coordinate = geographic_coordinate;
    _spherical_coordinate = spherical_coordinate;
    _velocity = velocity;
    _type = type;
}


FlightReport::FlightReport() {

}



OwnshipReport FlightReport::createOwnshipReport() {
    OwnshipReport ownshipReport;
    ownshipReport.set_timestamp(_time);
    ownshipReport.set_ownship_latitude(_geographic_coordinate.GetLatitude());
    ownshipReport.set_ownship_longitude(_geographic_coordinate.GetLongitude());
    ownshipReport.set_ownship_altitude(_geographic_coordinate.GetAltitude());
    ownshipReport.set_north(_velocity.north);
    ownshipReport.set_east(_velocity.east);
    ownshipReport.set_down(_velocity.down);

    return ownshipReport;
}

AdsBReport FlightReport::createAdsBReport() {
    AdsBReport adsBReport;
    adsBReport.set_timestamp(_time);
    adsBReport.set_latitude(_geographic_coordinate.GetLatitude());
    adsBReport.set_longitude(_geographic_coordinate.GetLongitude());
    adsBReport.set_altitude(_geographic_coordinate.GetAltitude());
    adsBReport.set_tail_number(_tail_number.Get());
    adsBReport.set_north(_velocity.north);
    adsBReport.set_east(_velocity.east);
    adsBReport.set_down(_velocity.down);

    return adsBReport;
}

RadarReport FlightReport::createRadarReport() {
    RadarReport radarReport;

    radarReport.set_timestamp(_time);
    radarReport.set_range(_spherical_coordinate.GetRange());
    radarReport.set_azimuth(_spherical_coordinate.GetAzimuth());
    radarReport.set_elevation(_spherical_coordinate.GetElevation());
    radarReport.set_id(_radar_id.Get());
    radarReport.set_north(_velocity.north);
    radarReport.set_east(_velocity.east);
    radarReport.set_down(_velocity.down);
    radarReport.set_latitude(_geographic_coordinate.GetLatitude());
    radarReport.set_longitude(_geographic_coordinate.GetLongitude());
    radarReport.set_altitude(_geographic_coordinate.GetAltitude());

    return radarReport;
}

TcasReport FlightReport::createTcasReport() {
    TcasReport tcasReport;

    tcasReport.set_id(_tcas_id.Get());
    tcasReport.set_range(_spherical_coordinate.GetRange());
    tcasReport.set_altitude(_geographic_coordinate.GetAltitude());
    return tcasReport;
}


CDTIPlane FlightReport::CreateCdtiPlane() {
    CDTIPlane cdti_plane;

    if (_type == ADSB) {
        cdti_plane.set_id(_tail_number.Get());
    }
    else if (_type == TCAS) {
        cdti_plane.set_id("" + _tcas_id.Get());
    }
    else if (_type == RADAR) {
        cdti_plane.set_id("" + _radar_id.Get());
    }
    Saas_Util::Vector<double, 3> position = _spherical_coordinate
            .ToCartesianCoordinates();
//    cdti_plane.set_allocated_position(&position);
 //   cdti_plane.set_allocated_velocity(&_velocity);

    return cdti_plane;
}

std::time_t FlightReport::GetTime() {
    return _time;
}

Device FlightReport::GetDevice() {
    return _type;
}

GeographicCoordinate FlightReport::GetGeographicCoordinate() {
    return _geographic_coordinate;
}

RadarID FlightReport::GetRadarID() {
    return _radar_id;
}

SphericalCoordinate FlightReport::GetSphericalCoordinate() {
    return _spherical_coordinate;
}

TailNumber FlightReport::GetTailNumber() {
    return _tail_number;
}

Velocity FlightReport::GetVelocity() {
    return _velocity;
}

TcasID FlightReport::GetTcasID() {
    return _tcas_id;
}

void FlightReport::PrintReport() {

    std::cout << "\ntime: " << _time << std::endl;
    std::cout << "tail number: " << _tail_number.Get() << std::endl;
    std::cout << "tcas id: " << (unsigned)_tcas_id.Get() << std::endl;
    std::cout << "radar id: " << _radar_id.Get() << std::endl;
    std::cout << "geographic coordinate(latitude): " <<
            _geographic_coordinate.GetLatitude()  << std::endl;
    std::cout << "geographic coordinate(longitude): " <<
        _geographic_coordinate.GetLongitude()  << std::endl;
    std::cout << "geographic coordinate(altitude): " <<
        _geographic_coordinate.GetAltitude()  << std::endl;
    std::cout << "spherical coordinate(range): " <<
        _spherical_coordinate.GetRange()  << std::endl;
  //  std::cout << "spherical coordinate(bearing): " <<
//        _spherical_coordinate.GetBearing()  << std::endl;
    std::cout << "geographic coordinate(azimuth): " <<
        _spherical_coordinate.GetAzimuth() << std::endl;
    std::cout << "geographic coordinate(elevation): " <<
        _spherical_coordinate.GetElevation() << std::endl;
    std::cout << "velocity north: " << _velocity.north << std::endl;
    std::cout << "velocity east: " << _velocity.east << std::endl;
    std::cout << "velocity down: " << _velocity.down << std::endl;
    std::cout << "device: " << _type << std::endl;
    std::cout << "\n";

}
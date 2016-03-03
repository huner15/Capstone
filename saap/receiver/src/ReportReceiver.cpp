/*
 * @file ReportReceiver.cpp
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style)
 * @date 2-18-16
 * @brief TODO make description
 */

#include "ReportReceiver.h"


ReportReceiver::ReportReceiver() {
    //TODO Make held reports use the constructor that takes in a correlation
    // engine
    _held_reports = HeldReports();
    _is_copying = false;
    pthread_mutex_init(&_radar_mutex, NULL);
    pthread_mutex_init(&_ownship_mutex, NULL);
    pthread_mutex_init(&_adsb_mutex, NULL);
    pthread_mutex_init(&_tcas_mutex, NULL);
    pthread_cond_init (&_held_report_cv, NULL);
    //TODO Make thread for calling Correlate and create Correlation Engine

}

FlightReport ReportReceiver::CreateOwnshipFlightReport(OwnshipReport report) {

    std::time_t time = report.timestamp();
    double latitude = report.ownship_longitude();
    double longitude = report.ownship_longitude();
    double altitude = report.ownship_altitude();
    double north = report.north();
    double down = report.down();
    double east = report.east();
    GeographicCoordinate geographic_coordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    Velocity velocity = Velocity(east, down, north);
    return FlightReport(time, TailNumber("      "), NULL,
                                              NULL,
                                              geographic_coordinate,
                                              SphericalCoordinate(0.0, 0.0,
                                                                 0.0),
                                              velocity, OWNSHIP);

}

SurveillanceReport* ReportReceiver::CreateTcasSurveillanceReport(
        TcasReport report) {
    TcasID tcas_id = TcasID(report.id());
    double range = report.range();
    double altitude = report.altitude();
    double bearing = report.bearing();
    GeographicCoordinate geographic_coordinate = GeographicCoordinate(0.0,
                                                                      0.0,
                                                                      altitude);
    Velocity velocity = Velocity(0.0, 0.0, 0.0);
    SphericalCoordinate spherical_coordinate = SphericalCoordinate(range, 0.0,
                                                                   bearing);

    FlightReport flight_report;
    flight_report = FlightReport(NULL, TailNumber("      "),
                                 tcas_id, NULL,
                                 geographic_coordinate,
                                 spherical_coordinate, velocity,
                                 TCAS);

    return new SurveillanceReport(flight_report);
}

SurveillanceReport* ReportReceiver::CreateAdsbSurveillanceReport(
        AdsBReport report) {
    std::time_t time = report.timestamp();
    double latitude = report.latitude();
    double longitude = report.longitude();
    double altitude = report.altitude();
    TailNumber tail_number = TailNumber(report.tail_number());
    double north = report.north();
    double down = report.down();
    double east = report.east();
    GeographicCoordinate geographic_coordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    Velocity velocity = Velocity(east, down, north);
    SphericalCoordinate spherical_coordinate = SphericalCoordinate(0.0, 0.0,
                                                                   0.0);

    FlightReport flight_report = FlightReport(time, tail_number, NULL, NULL,
                                              geographic_coordinate,
                                              spherical_coordinate, velocity,
                                              ADSB);

    return new SurveillanceReport(flight_report);

}

SurveillanceReport* ReportReceiver::CreateRadarSurveillanceReport(
        RadarReport report) {
    std::time_t time = report.timestamp();
    double range = report.range();
    double azimuth = report.azimuth();
    double elevation = report.elevation();
    double north = report.north();
    double down = report.down();
    double east = report.east();
    RadarID radar_id = RadarID(report.id());
    double latitude = report.latitude();
    double longitude = report.longitude();
    double altitude = report.altitude();

    GeographicCoordinate geographic_coordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    SphericalCoordinate spherical_coordinate = SphericalCoordinate(range,
                                                                   elevation,
                                                                   azimuth);
    Velocity velocity = Velocity(east, down, north);

    FlightReport flight_report;
    flight_report = FlightReport(time, TailNumber("      "), NULL,
                                 radar_id, geographic_coordinate,
                                 spherical_coordinate, velocity,
                                 RADAR);

    return new SurveillanceReport(flight_report);
}

void ReportReceiver::ReceiveOwnship(OwnshipReport report) {
    pthread_mutex_lock(&_ownship_mutex);
    while(_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_ownship_mutex);
    }
    _held_reports.changeOwnship(CreateOwnshipFlightReport(report));
    pthread_mutex_unlock(&_ownship_mutex);
}

void ReportReceiver::ReceiveTcas(TcasReport report) {
    pthread_mutex_lock(&_tcas_mutex);
    while(_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_tcas_mutex);
    }
    _held_reports.addTcasReport(CreateTcasSurveillanceReport(report));
    pthread_mutex_unlock(&_tcas_mutex);
}

void ReportReceiver::ReceiveAdsb(AdsBReport report) {
    pthread_mutex_lock(&_adsb_mutex);
    while (_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_adsb_mutex);
    }
    _held_reports.addAdsBReport(CreateAdsbSurveillanceReport(report));
    pthread_mutex_unlock(&_adsb_mutex);
}

void ReportReceiver::ReceiveRadar(RadarReport report) {
    pthread_mutex_lock(&_radar_mutex);
    while(_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_radar_mutex);
    }
    _held_reports.addRadarReport(CreateRadarSurveillanceReport(report));
    pthread_mutex_unlock(&_radar_mutex);
}


//Held Report data from here down

void ReportReceiver::HeldReports::changeOwnship(FlightReport report) {
    _ownship = report;
}

void ReportReceiver::HeldReports::addAdsBReport(SurveillanceReport * report) {
    _adsb_reports.push_back(report);
}

void ReportReceiver::HeldReports::addRadarReport(SurveillanceReport *report) {
    _radar_reports.push_back(report);
}

void ReportReceiver::HeldReports::addTcasReport(SurveillanceReport *report) {
    _tcas_reports.push_back(report);
}
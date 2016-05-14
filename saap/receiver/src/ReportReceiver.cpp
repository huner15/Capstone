/*
 * @file ReportReceiver.cpp
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style)
 * @date 2-18-16
 * @brief TODO make description
 */

#include "ReportReceiver.h"

ReportReceiver::ReportReceiver() {
    _held_reports = new ReceivedReports();
    _is_copying = false;
    _is_connected = true;
    pthread_mutex_init(&_radar_mutex, NULL);
    pthread_mutex_init(&_ownship_mutex, NULL);
    pthread_mutex_init(&_adsb_mutex, NULL);
    pthread_mutex_init(&_tcas_mutex, NULL);
    pthread_cond_init (&_held_report_cv, NULL);
}

ReportReceiver::~ReportReceiver() {
}

SurveillanceReport * ReportReceiver::CreateOwnshipSurveillanceReport
        (OwnshipReport report) {
    std::time_t time = report.timestamp();
    float latitude = report.ownship_latitude();
    double longitude = report.ownship_longitude();
    double altitude = report.ownship_altitude();
    double north = report.north();
    double down = report.down();
    double east = report.east();
    GeographicCoordinate geographic_coordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    Velocity velocity = Velocity(east, down, north);
    return new SurveillanceReport(time, TailNumber("      "), NULL,
                                  NULL,
                                  geographic_coordinate,
                                  SphericalCoordinate(0.0, 0.0,
                                                      0.0),
                                  velocity, OWNSHIP);
}

SurveillanceReport* ReportReceiver::CreateTcasSurveillanceReport(
        TcasReport report) {
    TcasID tcas_id = TcasID(report.id());
    double range = report.range() * NAUTICAL_MILES_TO_FEET;
    double altitude = report.altitude();
    double bearing = report.bearing();
    //TODO find a way to incorporate TCAS' altitude.
    GeographicCoordinate geographic_coordinate = GeographicCoordinate(0.0,
                                                                      0.0,
                                                                      0.0);
    Velocity velocity = Velocity(0.0, 0.0, 0.0);
    SphericalCoordinate spherical_coordinate = SphericalCoordinate(range, 0.0,
                                                                   bearing);

    return new SurveillanceReport(NULL, TailNumber("      "),
                                  tcas_id, NULL,
                                  geographic_coordinate,
                                  spherical_coordinate, velocity,
                                  TCAS);
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

    return new SurveillanceReport (time, tail_number, NULL, NULL,
                                   geographic_coordinate,
                                   spherical_coordinate, velocity,
                                   ADSB);
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

    return new SurveillanceReport (time, TailNumber("      "), NULL,
                                   radar_id, geographic_coordinate,
                                   spherical_coordinate, velocity,
                                   RADAR);
}

void ReportReceiver::ReceiveOwnship(OwnshipReport report) {
    pthread_mutex_lock(&_ownship_mutex);
    while (_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_ownship_mutex);
    }
    _held_reports->changeOwnship(CreateOwnshipSurveillanceReport(report));
    pthread_mutex_unlock(&_ownship_mutex);
}

void ReportReceiver::ReceiveTcas(TcasReport report) {
    pthread_mutex_lock(&_tcas_mutex);
    while (_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_tcas_mutex);
    }
    _held_reports->addTcasReport(CreateTcasSurveillanceReport(report));
    pthread_mutex_unlock(&_tcas_mutex);
}

void ReportReceiver::ReceiveAdsb(AdsBReport report) {
    pthread_mutex_lock(&_adsb_mutex);
    while (_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_adsb_mutex);
    }
    _held_reports->addAdsBReport(CreateAdsbSurveillanceReport(report));
    pthread_mutex_unlock(&_adsb_mutex);
}

void ReportReceiver::ReceiveRadar(RadarReport report) {
    pthread_mutex_lock(&_radar_mutex);
    while (_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_radar_mutex);
    }
    _held_reports->addRadarReport(CreateRadarSurveillanceReport(report));
    pthread_mutex_unlock(&_radar_mutex);
}

SurveillanceReport * ReportReceiver::getOwnship() {
    return _held_reports->GetOwnship();
}

vector<SurveillanceReport *>* ReportReceiver::getTcas() {
    return _held_reports->GetTcas();
}

vector<SurveillanceReport *>* ReportReceiver::getAdsB() {
    return _held_reports->GetAdsb();
}

vector<SurveillanceReport *>* ReportReceiver::getRadar() {
    return _held_reports->GetRadar();
}

ReceivedReports* ReportReceiver::GetReports() {
    return _held_reports;
}

void ReportReceiver::Clear() {
    _held_reports->Clear();
}

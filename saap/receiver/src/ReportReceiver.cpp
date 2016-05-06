/*
 * @file ReportReceiver.cpp
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style)
 * @date 2-18-16
 * @brief TODO make description
 */

#include <cstdlib>

#include "ReportReceiver.h"

CorrelationEngine* startEngine() {
    try {
        ClientSocket* client_socket = new ClientSocket("localhost", 13000);
        Categorizer* categorizer = new Categorizer(*client_socket);
        return new CorrelationEngine(*categorizer);
    }
    catch (SocketException exception) {
        std::cout << "Could not connect to CDTI." << std::endl;
        exit(EXIT_SUCCESS);
    }
}

ReportReceiver::ReportReceiver() {
    _held_reports = ReceivedReports();
    _is_copying = false;
    _is_connected = true;
    pthread_mutex_init(&_radar_mutex, NULL);
    pthread_mutex_init(&_ownship_mutex, NULL);
    pthread_mutex_init(&_adsb_mutex, NULL);
    pthread_mutex_init(&_tcas_mutex, NULL);
    pthread_cond_init (&_held_report_cv, NULL);

    _correlationEngine = startEngine();
}

ReportReceiver::~ReportReceiver() {
}

void ReportReceiver::Close() {
    _is_connected = false;
}

bool ReportReceiver::getIsConnected(){
    return _is_connected;
}

SurveillanceReport * ReportReceiver::CreateOwnshipSurveillanceReport
        (OwnshipReport report){

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
    //TODO find a way to incorporate tcas' altitude.
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
    while(_is_copying) {
        pthread_cond_wait(&_held_report_cv, &_ownship_mutex);
    }
    _held_reports.changeOwnship(CreateOwnshipSurveillanceReport(report));
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

SurveillanceReport * ReportReceiver::getOwnship() {
    return _held_reports.getOwnship();
}

vector<SurveillanceReport *>* ReportReceiver::getTcas() {
    return _held_reports.getTcas();
}

vector<SurveillanceReport *>* ReportReceiver::getAdsB() {
    return _held_reports.getAdsb();
}

vector<SurveillanceReport *>* ReportReceiver::getRadar() {
    return _held_reports.getRadar();
}

void ReportReceiver::callCorrelate() {
    /* TODO: Return ReceivedReport. */

    _is_copying = true;
    pthread_mutex_lock(&_radar_mutex);
    pthread_mutex_lock(&_tcas_mutex);
    pthread_mutex_lock(&_adsb_mutex);
    pthread_mutex_lock(&_ownship_mutex);

    std::vector<SurveillanceReport *>* tcas = _held_reports.CopyTcas();
    std::vector<SurveillanceReport *>* adsb = _held_reports.CopyAdsb();
    std::vector<SurveillanceReport *>* radar = _held_reports.CopyRadar();
    SurveillanceReport * ownship = _held_reports.CopyOwnship();

    _is_copying = false;
    pthread_cond_broadcast(&_held_report_cv);
    pthread_mutex_unlock(&_radar_mutex);
    pthread_mutex_unlock(&_tcas_mutex);
    pthread_mutex_unlock(&_adsb_mutex);
    pthread_mutex_unlock(&_ownship_mutex);


    //TODO make all of the copied held reports adsb relative
    _correlationEngine->Correlate(adsb, tcas, radar, false);
}

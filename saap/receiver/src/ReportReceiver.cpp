/*
 * @file ReportReceiver.cpp
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style)
 * @date 2-18-16
 * @brief TODO make description
 */

#include "ReportReceiver.h"


SurveillanceReport ReportReceiver::CreateOwnshipSurveillanceReport(
        OwnshipReport report) {

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
    FlightReport flight_report = FlightReport(time, TailNumber(""), NULL,
                                              NULL,
                                              geographic_coordinate,
                                              SphericalCoordinate(0.0, 0.0,
                                                                 0.0),
                                              velocity, OWNSHIP);
    return SurveillanceReport(flight_report);
}

SurveillanceReport ReportReceiver::CreateTcasSurveillanceReport(
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

    FlightReport flight_report = FlightReport(NULL, TailNumber(""), tcas_id,
                                              NULL, geographic_coordinate,
                                              spherical_coordinate, velocity,
                                              TCAS);

    return SurveillanceReport(flight_report);
}

SurveillanceReport ReportReceiver::CreateAdsbSurveillanceReport(
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

    return SurveillanceReport(flight_report);

}

SurveillanceReport ReportReceiver::CreateRadarSurveillanceReport(
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

    FlightReport flight_report = FlightReport(time, TailNumber(""), NULL,
                                              radar_id, geographic_coordinate,
                                              spherical_coordinate, velocity,
                                              RADAR);

    return SurveillanceReport(flight_report);
}

void ReportReceiver::ReceiveOwnship(OwnshipReport report) {
    _ownship = CreateOwnshipSurveillanceReport(report);
}

void ReportReceiver::ReceiveTcas(TcasReport report) {
    _tcas_reports.push_back(CreateTcasSurveillanceReport(report));
}

void ReportReceiver::ReceiveAdsb(AdsBReport report) {
    _adsb_reports.push_back(CreateAdsbSurveillanceReport(report));
}

void ReportReceiver::ReceiveRadar(RadarReport report) {
    _radar_reports.push_back(CreateRadarSurveillanceReport(report));
}

void ReportReceiver::ClearReports() {
    _tcas_reports.clear();
    _adsb_reports.clear();
    _radar_reports.clear();
}

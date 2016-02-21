/*
 * @file ReportReceiver.cpp
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief TODO make description
 */

#include "ReportReceiver.h"


SurveillanceReport ReportReceiver::createOwnshipSurveillanceReport(
        OwnshipReport report) {

    std::time_t time = report.timestamp();
    double latitude = report.ownship_longitude();
    double longitude = report.ownship_longitude();
    double altitude = report.ownship_altitude();
    double north = report.north();
    double down = report.down();
    double east = report.east();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    Velocity velocity = Velocity(east, down, north);
    FlightReport flightReport = FlightReport(time, TailNumber(""), NULL,
                                             NULL,
                                             geographicCoordinate,
                                             SphericalCoordinate(0.0, 0.0,
                                                                 0.0),
                                             velocity, OWNSHIP);
    return SurveillanceReport(flightReport);
}

SurveillanceReport ReportReceiver::createTcasSurveillanceReport(
        TcasReport report) {
    TcasID tcasID = TcasID(report.id());
    double range = report.range();
    double altitude = report.altitude();
    double bearing = report.bearing();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(0.0,
                                                                     0.0,
                                                                     altitude);
    Velocity velocity = Velocity(0.0, 0.0, 0.0);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(range, 0.0,
                                                                  bearing);

    FlightReport flightReport = FlightReport(NULL, TailNumber(""), tcasID,
                                             NULL, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             TCAS);

    return SurveillanceReport(flightReport);
}

SurveillanceReport ReportReceiver::createAdsBSurveillanceReport(
        AdsBReport report) {
    std::time_t time = report.timestamp();
    double latitude = report.latitude();
    double longitude = report.longitude();
    double altitude = report.altitude();
    TailNumber tailNumber = TailNumber(report.tail_number());
    double north = report.north();
    double down = report.down();
    double east = report.east();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    Velocity velocity = Velocity(east, down, north);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(0.0, 0.0,
                                                                  0.0);

    FlightReport flightReport = FlightReport(time, tailNumber, NULL, NULL,
                                             geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             ADSB);

    return SurveillanceReport(flightReport);

}

SurveillanceReport ReportReceiver::createRadarSurveillanceReport(
        RadarReport report) {
    std::time_t time = report.timestamp();
    double range = report.range();
    double azimuth = report.azimuth();
    double elevation = report.elevation();
    double north = report.north();
    double down = report.down();
    double east = report.east();
    RadarID radarID = RadarID(report.id());
    double latitude = report.latitude();
    double longitude = report.longitude();
    double altitude = report.altitude();

    GeographicCoordinate geographicCoordinate = GeographicCoordinate
            (latitude, longitude, altitude);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(range,
                                                                  elevation,
                                                                  azimuth);
    Velocity velocity = Velocity(east, down, north);

    FlightReport flightReport = FlightReport(time, TailNumber(""), NULL,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             RADAR);

    return SurveillanceReport(flightReport);
}

void ReportReceiver::ReceiveOwnship(OwnshipReport report) {
    ownship = createOwnshipSurveillanceReport
            (report);
}

void ReportReceiver::ReceiveTcas(TcasReport report) {
    tcasReports.push_back(createTcasSurveillanceReport(report));
}

void ReportReceiver::ReceiveAdsb(AdsBReport report) {
    adsbReports.push_back(createAdsBSurveillanceReport(report));
}

void ReportReceiver::ReceiveRadar(RadarReport report) {
    radarReports.push_back(createRadarSurveillanceReport(report));
}

void ReportReceiver::clearReports() {
    tcasReports.clear();
    adsbReports.clear();
    radarReports.clear();
}

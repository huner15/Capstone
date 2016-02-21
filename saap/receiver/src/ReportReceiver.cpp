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
    SurveillanceReport surveillanceReport = SurveillanceReport(flightReport);
    return surveillanceReport;
}

void ReportReceiver::ReceiveOwnship(OwnshipReport report) {
    ownship = createOwnshipSurveillanceReport
            (report);

}

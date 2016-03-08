/*
 * @file FlightReport.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 3-7-16
 * @brief TODO: Description
 */

#ifndef ACTUAL_REPORT_H_
#define ACTUAL_REPORT_H_

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

class FlightReport {
private:
    AdsBReport _adsb_report;
    RadarReport _radar_report;
    TcasReport _tcas_report;
    OwnshipReport _ownship_report;

public:

    /* TODO: Create constructors for all 16 report combinations.
    FlightReport(AdsBReport adsb_report, RadarReport radar_report,
                 OwnshipReport ownship_report);

    FlightReport(AdsBReport adsb_report, TcasReport tcas_report,
                 OwnshipReport ownship_report);
    */

    FlightReport(AdsBReport adsb_report, RadarReport radar_report,
                 TcasReport tcas_report, OwnshipReport ownship_report);

    bool HasAsdbReport();

    bool HasRadarReport();

    bool HasTcasReport();

    bool HasOwnshipReport();

    AdsBReport GetAdsbReport();

    RadarReport GetRadarReport();

    TcasReport GetTcasReport();

    OwnshipReport GetOwnshipReport();
};

#endif

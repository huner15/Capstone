/*
 * @file FlightReport.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 3-7-16
 * @brief TODO: Description
 */

#include "FlightReport.h"

FlightReport::FlightReport(AdsBReport adsb_report, RadarReport radar_report,
        TcasReport tcas_report, OwnshipReport ownship_report) {
    _adsb_report = adsb_report;
    _radar_report = radar_report;
    _tcas_report = tcas_report;
    _ownship_report = ownship_report;
}

bool FlightReport::HasAsdbReport() {
    return _adsb_report.has_timestamp();
}

bool FlightReport::HasRadarReport() {
    return _radar_report.has_timestamp();
}

bool FlightReport::HasTcasReport() {
    return _tcas_report.has_id();
}

bool FlightReport::HasOwnshipReport() {
    return _ownship_report.has_timestamp();
}

AdsBReport FlightReport::GetAdsbReport() {
    return _adsb_report;
}

RadarReport FlightReport::GetRadarReport() {
    return _radar_report;
}

TcasReport FlightReport::GetTcasReport() {
    return _tcas_report;
}

OwnshipReport FlightReport::GetOwnshipReport() {
    return _ownship_report;
}

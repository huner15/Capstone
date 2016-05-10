/*
 * @file ReceivedReports.cpp
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 4-25-16
 * @brief TODO make description
 */

#include "ReceivedReports.h"

ReceivedReports::ReceivedReports() {
    _ownship = new SurveillanceReport();
    _adsb_reports = new std::vector<SurveillanceReport *>();
    _radar_reports = new std::vector<SurveillanceReport *>();
    _tcas_reports = new std::vector<SurveillanceReport *>();
}

void ReceivedReports::changeOwnship(SurveillanceReport *report) {
    _ownship = report;
}

void ReceivedReports::addAdsBReport(SurveillanceReport * report) {
    _adsb_reports->push_back(report);
}

void ReceivedReports::addRadarReport(SurveillanceReport *report) {
    _radar_reports->push_back(report);
}

void ReceivedReports::addTcasReport(SurveillanceReport *report) {
    _tcas_reports->push_back(report);
}


SurveillanceReport* ReceivedReports::GetOwnship() {
    return _ownship;
}

std::vector<SurveillanceReport *>* ReceivedReports::GetAdsb() {
    return _adsb_reports;
}

std::vector<SurveillanceReport *>* ReceivedReports::GetRadar() {
    return _radar_reports;
}

std::vector<SurveillanceReport *>* ReceivedReports::GetTcas() {
    return _tcas_reports;
}

bool ReceivedReports::MakeRelative() {
    //TODO actually put in the logic to make adsb relative here.
    return false;
}


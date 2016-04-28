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


SurveillanceReport* ReceivedReports::getOwnship() {
    return _ownship;
}

std::vector<SurveillanceReport *>* ReceivedReports::getAdsb() {
    return _adsb_reports;
}

std::vector<SurveillanceReport *>* ReceivedReports::getRadar() {
    return _radar_reports;
}

std::vector<SurveillanceReport *>* ReceivedReports::getTcas() {
    return _tcas_reports;
}

std::vector<SurveillanceReport *>* ReceivedReports::CopyTcas() {
    std::vector<SurveillanceReport *>* newVector = new
            std::vector<SurveillanceReport *>();
    std::vector<SurveillanceReport *> hold = *_tcas_reports;
    newVector->swap(hold);
    return newVector;
}

std::vector<SurveillanceReport *>* ReceivedReports::CopyAdsb() {
    std::vector<SurveillanceReport *>* newVector = new
            std::vector<SurveillanceReport *>();
    std::vector<SurveillanceReport *> hold = *_adsb_reports;
    newVector->swap(hold);
    return newVector;
}

std::vector<SurveillanceReport *>* ReceivedReports::CopyRadar() {
    std::vector<SurveillanceReport *>* newVector = new
            std::vector<SurveillanceReport *>();
    std::vector<SurveillanceReport *> hold = *_radar_reports;
    newVector->swap(hold);
    return newVector;
}

SurveillanceReport* ReceivedReports::CopyOwnship() {
    SurveillanceReport * report = _ownship;
    _ownship = new SurveillanceReport();
    return report;
}
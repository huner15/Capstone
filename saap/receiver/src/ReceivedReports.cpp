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

ReceivedReports::ReceivedReports(const ReceivedReports& other){
    _ownship = new SurveillanceReport(*other._ownship);
    _adsb_reports = new std::vector<SurveillanceReport *>();
    _radar_reports = new std::vector<SurveillanceReport *>();
    _tcas_reports = new std::vector<SurveillanceReport *>();
    for(int i = 0; i < other._adsb_reports->size(); i++){
        _adsb_reports->push_back(new SurveillanceReport
                                         (*other._adsb_reports->at(i)));
    }
    for (int j = 0; j < other._radar_reports->size(); j++){
        _radar_reports->push_back(new SurveillanceReport
                                          (*other._radar_reports->at(j)));
    }
    for (int k = 0; k < other._tcas_reports->size(); k++){
        _tcas_reports->push_back(new SurveillanceReport
                                         (*other._tcas_reports->at(k)));
    }
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


/*
 * @file ReportReceiver.h
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief TODO make description
 */

#ifndef SAAS_REPORTRECEIVER_H
#define SAAS_REPORTRECEIVER_H

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>
#include <cdti.pb.h>
#include "SurveillanceReport.h"



class ReportReceiver {
public:
    /*
     * Takes in an OwnshipReport from the Simulation Server and sends it to
     * Create Ownship to create a SurveillanceReport. Then changes out the
     * ownship Surveillance report with the new one generated.
     * @param report A report received from the Simulation Server
     */
    void ReceiveOwnship (OwnshipReport report);
    void ReceiveTcas(TcasReport report);
    void ReceiveAdsb(AdsBReport report);
    void ReceiveRadar(RadarReport report);

    void clearReports();

private:
    std::vector<SurveillanceReport> tcasReports;
    std::vector<SurveillanceReport> adsbReports;
    std::vector<SurveillanceReport> radarReports;
    SurveillanceReport ownship;

    /*
     * Takes the OwnshipReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveOwnship.
     * @return the created Surveillance Report
     */
    SurveillanceReport createOwnshipSurveillanceReport(OwnshipReport report);
    SurveillanceReport createTcasSurveillanceReport(TcasReport report);
    SurveillanceReport createRadarSurveillanceReport(RadarReport report);
    SurveillanceReport createAdsBSurveillanceReport(AdsBReport report);

};


#endif //SAAS_REPORTRECEIVER_H

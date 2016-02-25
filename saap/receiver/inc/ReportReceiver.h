/*
 * @file ReportReceiver.h
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style)
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
private:
    std::vector<SurveillanceReport> _tcas_reports;
    std::vector<SurveillanceReport> _adsb_reports;
    std::vector<SurveillanceReport> _radar_reports;
    SurveillanceReport _ownship;

    /*
     * Takes the OwnshipReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveOwnship.
     * @return the created Surveillance Report
     */
    SurveillanceReport CreateOwnshipSurveillanceReport(OwnshipReport report);

    /*
     * Takes the TcasReport and translates it into a Surveillance Report.
     * @param report a Report received from ReceiveTcas.
     * @return The created Surveillance Report
     */
    SurveillanceReport CreateTcasSurveillanceReport(TcasReport report);
    /*
     * Takes the RadarReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveRadar.
     * @return the created Surveillance Report
     */
    SurveillanceReport CreateRadarSurveillanceReport(RadarReport report);
    /*
     * Takes the AdsBReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveAdsB.
     * @return the created Surveillance Report
     */
    SurveillanceReport CreateAdsbSurveillanceReport(AdsBReport report);
public:
    /*
     * Takes in an OwnshipReport from the Simulation Server and sends it to
     * Create Ownship to create a SurveillanceReport. Then changes out the
     * ownship Surveillance report with the new one generated.
     * @param report A report received from the Simulation Server
     */
    void ReceiveOwnship(OwnshipReport report);
    /*
     * Takes in a TcasReport from the Simulation Server and sends it to
     * CreateTcasSurveillanceReport to get the Surveillance report to add to
     * the tcasReports.
     */
    void ReceiveTcas(TcasReport report);
    /*
     * Takes in a AdsBReport from the Simulation Server and sends it to
     * CreateAdsBSurveillanceReport to get the Surveillance report to add to
     * the AdsBReports.
     */
    void ReceiveAdsb(AdsBReport report);
    /*
    * Takes in a RadarReport from the Simulation Server and sends it to
    * CreateRadarSurveillanceReport to get the Surveillance report to add to
    * the RadarReports.
    */
    void ReceiveRadar(RadarReport report);

    /*
     * Clears all the reports but ownship, so that they aren't confused with
     * the next second's
     */
    void ClearReports();

    /*
     * Gets the tcasReports
     * @return the current vector of tcasReports
     */
    std::vector<SurveillanceReport> GetTcasReports() {
        return _tcas_reports;
    }

    /*
     * Gets the adsBReports
     * @return the current vector of adsBReports
     */
    std::vector<SurveillanceReport> GetAdsbReports() {
        return _adsb_reports;
    }

    /*
     * Gets the radarReports
     * @return the current vector of radarReports
     */
    std::vector<SurveillanceReport> GetRadarReports() {
        return _radar_reports;
    }

    /*
     * Gets the current ownship
     * @return the current ownship
     */
    SurveillanceReport GetOwnship() {
        return _ownship;
    }
};


#endif //SAAS_REPORTRECEIVER_H

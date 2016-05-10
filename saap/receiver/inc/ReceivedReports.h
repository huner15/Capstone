/*
 * @file ReceivedReports.h
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 4-25-16
 * @brief TODO make description
 */

#ifndef RECEIVED_REPORTS_H_
#define RECEIVED_REPORTS_H_

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>
#include <cdti.pb.h>

#include "SurveillanceReport.h"


class ReceivedReports {
private:
    std::vector<SurveillanceReport *>* _tcas_reports;
    std::vector<SurveillanceReport *>* _adsb_reports;
    std::vector<SurveillanceReport *>* _radar_reports;
    SurveillanceReport * _ownship;

    /*
     * Creates a copy of the specified vector. This copy uses the ownship
     * FlightReport to make the Surveillance report relative. This should
     * only be called on a copy of the held report.
     */
    std::vector<SurveillanceReport *>* makeCopyOfVector
            (std::vector<SurveillanceReport *>);

public:
    ReceivedReports();

    /*
     * Gets the current vector of Surveillance Report * for Tcas.
     * @return the current vector for tcas.
     */
    std::vector<SurveillanceReport *>* getTcas();

    /*
     * Gets the current vector of Surveillance Report * for adsb
     * @return the current vector for adsb
     */
    std::vector<SurveillanceReport *>* getAdsb();

    /*
     * Gets the current vector of Surveillance Report * for radar
     * @return the current vector for radar
     */
    std::vector<SurveillanceReport *>* getRadar();

    /*
     * Gets the Current Surveillance Report for ownship
     */
    SurveillanceReport* getOwnship();

    /*
     * Adds a SurveillanceReport pointer to the Tcas Reports
     * @param report The tcas report that needs to be added.
     */
    void addTcasReport(SurveillanceReport * report);

    /*
     * Adds a SurveillanceReport pointer to the Adsb Reports
     * @param report the adsb report that needs to be added
     */
    void addAdsBReport(SurveillanceReport * report);

    /*
     * Adds a SurveillanceReport pointer to the Radar Reports
     * @param report the radar report that needs to be added.
     */
    void addRadarReport(SurveillanceReport * report);

    /*
     * Changes the current ownship FlightReport
     * @param report the ownship report to replace the last.
     */
    void changeOwnship(SurveillanceReport * report);

    /*
     * Swaps out the current data into a return vector and clears the
     * current vector of tcas surveillance reports
     * @return a different place for the current tcas reports.
     */
    std::vector<SurveillanceReport *>* CopyTcas();

    /*
     * Swaps out the current data into a return vector and clears the
     * current vector of Adsb surveillance reports
     * @return a different place for the current Adsb reports.
     */
    std::vector<SurveillanceReport *>* CopyAdsb();

    /*
     * Swaps out the current data into a return vector and clears the
     * current vector of radar surveillance reports
     * @return a different place for the current radar reports.
     */
    std::vector<SurveillanceReport *>* CopyRadar();

    /*
     * Gets the current ownship and clears the ownship inside of held
     * reports
     */
    SurveillanceReport* CopyOwnship();
};

#endif

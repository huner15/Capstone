/*
 * @file ReportReceiver.h
 * @author Specific Atomics
 * @author Alanna Buss, Dat Tran (style), Frank Poole
 * @date 5-13-2016
 * @brief TODO make description
 */

#ifndef REPORT_RECEIVER_H_
#define REPORT_RECEIVER_H_

#include <cstdlib>

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>
#include <cdti.pb.h>

#include "SurveillanceReport.h"
#include "ReceivedReports.h"

class ReportReceiver {
private:
    ReceivedReports* _held_reports;

    bool _is_copying;
    bool _is_connected;

    pthread_cond_t _held_report_cv;
    pthread_mutex_t _radar_mutex;
    pthread_mutex_t _tcas_mutex;
    pthread_mutex_t _adsb_mutex;
    pthread_mutex_t _ownship_mutex;

    static constexpr double NAUTICAL_MILES_TO_FEET = 6076.12;

    /*
     * Takes the OwnshipReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveOwnship.
     * @return the created Surveillance Report
     */
    SurveillanceReport * CreateOwnshipSurveillanceReport(OwnshipReport
                                                         report);

    /*
     * Takes the TcasReport and translates it into a Surveillance Report.
     * @param report a Report received from ReceiveTcas.
     * @return The created Surveillance Report
     */
    SurveillanceReport* CreateTcasSurveillanceReport(TcasReport report);
    /*
     * Takes the RadarReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveRadar.
     * @return the created Surveillance Report
     */
    SurveillanceReport* CreateRadarSurveillanceReport(RadarReport report);
    /*
     * Takes the AdsBReport and translates it to a Surveillance report.
     * @param report A report received from the ReceiveAdsB.
     * @return the created Surveillance Report
     */
    SurveillanceReport* CreateAdsbSurveillanceReport(AdsBReport report);

public:
    /*
     * Initializes the thread for countdown, creates all the locks and
     * creates the correct correlation engine.
     */
    ReportReceiver();

    /**
     * Deconstruct the report receiver.
     */
    ~ReportReceiver();

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
     * Gets the current ownship report.
     * @return the ownship surveillance report
     */
    SurveillanceReport* getOwnship();

    /*
     * Gets the current vector pointer of tcas reports.
     * @return the vector pointer of tcas surveillance report pointers.
     */
    vector<SurveillanceReport *>* getTcas();

    /*
     * Gets the current vector pointer of adsb reports.
     * @return the vector pointer of adsb surveillance report pointers
     */
    vector<SurveillanceReport *>* getAdsB();

    /*
     * Gets the current vector pointer of radar reports
     * @return the vector pointer of radar surveillance report pointers
     */
    vector<SurveillanceReport *>* getRadar();

    /*
     * Calls the correlate function in CorrelationEngine using the copied
     * reports from heldreports after making all of the adsb reports relative.
     */
    ReceivedReports* GetReports();

    /**
     * Clear all reports held in this report receiver.
     */
    void Clear();
};

#endif

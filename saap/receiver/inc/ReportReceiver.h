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
#include "CorrelationEngine.h"

class ReportReceiver {
private:

    const double NAUTICAL_MILES_TO_FEET = 6076.12;

    class HeldReports {
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
        //HeldReports(CorrelationEngine corEngine);

        HeldReports();

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

    bool _is_copying;
    pthread_cond_t _held_report_cv;
    pthread_mutex_t _radar_mutex;
    pthread_mutex_t _tcas_mutex;
    pthread_mutex_t _adsb_mutex;
    pthread_mutex_t _ownship_mutex;
    HeldReports _held_reports;
    pthread_t countThread;
    CorrelationEngine correlationEngine;

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

    /*
     * Calls the correlate function in CorrelationEngine using the copied
     * reports from heldreports after making all of the adsb reports relative.
     */
    void callCorrelate();


public:

    /*
     * Initializes the thread for countdown, creates all the locks and
     * creates the correct correlation engine.
     */
    ReportReceiver();

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
    * For the count thread. It just goes and calls correlate every second.
    */
    static void *TimerThreadFunction(void* classReference);

    int num;
};




#endif //SAAS_REPORTRECEIVER_H
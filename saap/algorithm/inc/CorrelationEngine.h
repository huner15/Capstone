/**
* @file CorrelationEngine.h
* @author Specific Atomics
* @author Andrea Savage
* @date 3-4-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the interchangeable algorithms will be based on.
*/

#ifndef SAAS_CORRELATIONENGINE_H
#define SAAS_CORRELATIONENGINE_H

#include <Categorizer.h>
#include "SurveillanceReport.h"
#include "Cluster.h"
#include "CorrelationAircraft.h"

#define TRUE 0
#define FALSE 1
#define MINDISTANCE 0.9
#define MAXLATITUDE 0.0001 //degrees
#define MAXLONGITUDE 0.0001 //degrees
#define MAXALTITUDE 50 //feet

using namespace std;

class CorrelationEngine {
protected:
    vector<Cluster *> _clusters;
    vector<Cluster *> _free_clusters;
    vector<CorrelationAircraft *> _corr_aircraft;
    vector<CorrelationAircraft *> _free_aircraft;
    bool _is_relative;

public:
    CorrelationEngine();

    ~CorrelationEngine();

    /**
     * Runs the Algorithm to create all of the Clusters.
     * Will be overridden by each class that extends this class.
     * @param adsb The reports received from the ADS-B hardware for the current sec
     * @param radar The reports received from the radar hardware for the current sec
     * @param tcas The reports received from the TCAS hardware for the current sec
     */
    void RunAlgorithm(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,
        vector<SurveillanceReport *> *radar);

    /**
     * Main method of the correlation algorithm.
     * Called from the ReportReceiver.
     * Takes in all of the SurveillanceReports, adds SurveillanceReports to
     * all of the possible Clusters for each SurveillanceReport, generates
     * Clusters, and evaluates each detected aircraft location.
     *
     * @param adsb The reports received from the ADS-B hardware for the current sec
     * @param radar The reports received from the radar hardware for the current sec
     * @param tcas The reports received from the TCAS hardware for the current sec
     * @param is_relative if ADS-B has a calculated Spherical Coordinate
     * @return int 0 for success, 1 for error
     */
    int Correlate(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,vector<SurveillanceReport *> *radar,
        bool is_relative);

    /**
     * Compares the given TCAS report to all of the current clusters to
     * look for a match and add it to the best cluster if there is one. This
     * method is a helper method for the current RunAlgorithm method.
     * @param report The TCAS report to compare by
     * @return double Whether or not the report was added to a current cluster
     */
    double CompareTcasToClusters(SurveillanceReport *report);

    /**
     * Compares the given radar report to all of the current clusters to
     * look for a match and add it to the best cluster if there is one. This
     * method is a helper method for the current RunAlgorithm method.
     * @param report The radar report to compare by
     * @return double Whether or not the report was added to a current cluster
     */
    double CompareRadarToClusters(SurveillanceReport *report);

    /**
     * Converts a given Cluster into a CorrelateAircraft by averaging
     * the reports' fields excluding outliers.
     * @param cluster The cluster to get data from
     * @return int 0 for success, 1 for error
     */
    int ConvertAircraft(Cluster *cluster);

    /*
     * Checks that all Clusters have atleast one SurveillanceReport.
     * Ran after all CorrelatedAircraft are calculated by the algorithm.
     *
     * @return int 0 for success, 1 for error
     */
    int CheckClusterCount();

    /*
     * Gets an empty Cluster pointer from the existing list or
     * mallocs a new one.
     * @return Cluster * the pointer to the new Cluster to use
     */
    Cluster *NewCluster();

    /*
     * Gets an empty Cluster pointer from the existing list or
     * mallocs a new one.
     * @return Cluster * the pointer to the new Cluster to use
     */
    CorrelationAircraft *NewCorrAircraft();

    /*
     * Generates the distance between two SurveillanceReports
     * based on their speed, heading, and distance.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return float The distance metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcDistance(SurveillanceReport *reportOne, SurveillanceReport
        *reportTwo);

    /**
     * Helper function that calculates the heading correlation ranking between two
     * Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return double The heading metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcHeading(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    /**
     * Helper function that calculates the velocity correlation ranking between two
     * Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return float The velocity metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcVelocity(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    /**
     * Helper function that calculates the Euclidean distance correlation ranking
     * between two Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return double The Euclidean distance metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcEuclidDistance(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    /**
     * Helper function that calculates the error of the given device type.
     *
     * @param reportOne The report to evaluate
     * @return float The error of this report device type
     */
    double CalcVelocityError(Device type);
};

#endif
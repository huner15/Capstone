/**
* @file CorrelationEngine.h
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the interchangeable algorithms will be based on.
*/

#ifndef CORRELATION_ENGINE_H_
#define CORRELATION_ENGINE_H_

#include <pthread.h>

#include "SurveillanceReport.h"
#include "Cluster.h"
#include "CorrelationAircraft.h"
#include "GenerationMath.h"
#include "ReceivedReports.h"
#include "Correlator.h"
#include <ReportReceiver.h>

#define TRUE 0
#define FALSE 1
#define MINDISTANCE 0.9 //Minimum distance to cluster by
#define MAXLATITUDEERROR 0.0001 //degrees
#define MAXLONGITUDEERROR 0.0001 //degrees
#define MAXALTITUDEERROR 50 //feet
#define MAXAZIMUTHERROR 360 //degrees
#define MAXELEVATIONERROR 180 //degrees
#define MAXRADARERROR 50 //feet
#define EXITVAL -1

using namespace std;

class CorrelationEngine: public Correlator {
protected:
    // Holds the Clusters generated for this second
    vector<Cluster *> _clusters;
    // Holds the Correlation Aircraft objects generated this second
    vector<CorrelationAircraft *> _corr_aircraft;

    // Whether or not ADS-B reports where converted to relative this second
    bool _is_relative;

    // Mutex locks for using the cluster and corrAircraft vectors.
    pthread_mutex_t cluster_mutex;
    pthread_mutex_t corr_aircraft_mutex;

    /*
     * Checks that all Clusters have at least one SurveillanceReport.
     * Ran after all CorrelatedAircraft are calculated by the algorithm.
     *
     * @return int 0 for success, 1 for error
     */
    int CheckClusterCount();

private:
    /**
     * Compares two geographical coordinates to calculate the spherical
     * coordinate relation between the two points.
     * @param aircraft the first geographical point
     * @param ownship the second geographical point
     * @return SphericalCoordinate the calculated relative coordinate of
     * aircraft
     */
    SphericalCoordinate ConvertGeoToSpher(GeographicCoordinate *aircraft,
                                          GeographicCoordinate *ownship);

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
     * Helper function that calculates the error of the given device type.
     *
     * @param reportOne The report to evaluate
     * @return float The error of this report device type
     */
    double CalcVelocityError(Device type);

    // Use mutex locks when true.
    bool mutexs = true;

public:
    /*
     * No parameter constructor, sets _is_relative to true.
     */
    CorrelationEngine();

    /*
     * Empty deconstructor, does nothing.
     */
    ~CorrelationEngine();

    /*
     * Returns the current size of the clusters vector.
     * @int _clusters size
     */
    int GetClusterSize();

    /**
     * Runs the Algorithm to create all of the Clusters.
     * Will be overridden by each class that extends this class.
     * @param adsb The reports received from the ADS-B hardware for the
     * current sec
     * @param radar The reports received from the radar hardware for the
     * current sec
     * @param tcas The reports received from the TCAS hardware for the
     * current sec
     * @return 0 for success, -1 for error
     */
    int RunAlgorithm(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,
        vector<SurveillanceReport *> *radar);

    /**
     * Main method of the correlation algorithm.
     * Called from the ReportReceiver.
     * Takes in all of the SurveillanceReports, adds SurveillanceReports to
     * all of the possible Clusters for each SurveillanceReport, generates
     * Clusters, and evaluates each detected aircraft location.
     *
     * @param reports the reports received in the last second.
     * @return vector of Clusters
     */
    std::vector<CorrelationAircraft *>* Correlate(ReceivedReports reports);

    /**
     * Converts a given Cluster into a CorrelateAircraft by averaging
     * the reports' fields excluding outliers.
     * @param cluster The cluster to get data from
     * @return CorrelationAircraft *A pointer to the generated aircraft.
     */
    CorrelationAircraft *ConvertAircraft(Cluster *cluster);

    /*
     * Gets an empty Cluster pointer from the existing list or
     * mallocs a new one.
     * @return Cluster * the pointer to the new Cluster to use
     */
    Cluster *NewCluster();

    /*
     * Generates the distance between two SurveillanceReports
     * based on their velocity, heading, and distance.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return float The distance metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcDistance(SurveillanceReport *reportOne, SurveillanceReport
        *reportTwo);

    /**
     * Helper function that calculates the heading correlation ranking between
     * two Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return double The heading metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcHeading(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    /**
     * Helper function that calculates the velocity correlation ranking between
     * two Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return float The velocity metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcVelocity(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    /**
     * Helper function that calculates the Euclidean distance correlation
     * ranking between two Surveillance Reports for the distance metric.
     *
     * @param reportOne The first report to compare
     * @param reportTwo The second report to compare
     * @return double The Euclidean distance metric from 0 to 1 where 1 is the
     * highest correlation.
     */
    double CalcEuclidDistance(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);
};

#endif

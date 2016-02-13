/**
* @file Cluster.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Calculates the distance matrices from three sets of input Surveillance
 * Reports and then generates the Clusters.
*/

#include <cmath>
#include "Cluster.h"
#include <vector>
#include "CorrelationAircraft.h"

#define REPORTS 10

using namespace std;

vector<Cluster> clusters;

/*
 * Main method of the correlation algorithm.
 * Called from the ReportReceiver.
 * Takes in all of the SurveillanceReports,
 * adds SurveillanceReports to all of the
 * possible Clusters for each FlightReport,
 * generates Clusters, and evaluates each
 * detected aircraft location.
 *
 * @param ownship The report received from the ownship for the current second
 * @param adsb The reports received from the ADS-B hardware for the current sec
 * @param radar The reports received from the radar hardware for the current sec
 * @param tcas The reports received from the TCAS hardware for the current sec
 * @return int 0 for success, 1 for error
 */
int Correlate(vector<FlightReport> adsb,
    vector<FlightReport> tcas, FlightReport ownship,
    vector<FlightReport> radar);

/*
 * Checks that all SurveillanceReports are in
 * exactly one Cluster.
 * Ran after all CorrelatedAircraft are
 * calculated by the algorithm.
 *
 * @return int 0 for success, 1 for error
 */
int CheckClusterCount();

/*
 * Generates the distance between two SurveillanceReports
 * based on their speed, heading, and distance.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The distance metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float CalcDistance(FlightReport reportOne, FlightReport reportTwo)
{
    float distance = CalcHeading(reportOne, reportTwo);
    distance += CalcEuclidDistance(reportOne, reportTwo);
    distance += CalcSpeed(reportOne, reportTwo);

    return cbrt(distance);
}

/**
 * Helper function that calculates the heading correlation ranking between two
 * Surveillance Reports for the distance metric.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The heading metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float CalcHeading(FlightReport reportOne, FlightReport reportTwo)
{
    return 0;
}

/**
 * Helper function that calculates the Euclidean distance correlation ranking
 * between two Surveillance Reports for the distance metric.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The Euclidean distance metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float CalcEuclidDistance(FlightReport reportOne, FlightReport
reportTwo)
{
    return 0;
}


/**
 * Helper function that calculates the speed correlation ranking between two
 * Surveillance Reports for the distance metric.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The speed metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float CalcSpeed(FlightReport reportOne, FlightReport reportTwo)
{
    return 0;
}
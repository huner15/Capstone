/**
* @file Cluster.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Calculates the distance matrices from three sets of input Surveillance
 * Reports and then generates the Clusters.
*/

#include <Vector.h>
#include <cmath>
#include "Cluster.h"

#define REPORTS 10

Vector<Cluster, REPORTS> clusters;

/*
 * Main method of the correlation algorithm.
 * Called from the ReportReceiver.
 * Takes in all of the SurveillanceReports,
 * adds SurveillanceReports to all of the
 * possible Clusters for each SurveillanceReport,
 * generates Clusters, and evaluates each
 * detected aircraft location.
 *
 * @param ownship The report received from the ownship for the current second
 * @param adsb The reports received from the ADS-B hardware for the current second
 * @param radar The reports received from the radar hardware for the current second
 * @param tcas The reports received from the TCAS hardware for the current second
 * @return int 0 for success, 1 for error
 */
int correlate(SurveillanceReport ownship, Vector<SurveillanceReport, REPORTS> adsb,
              Vector<SurveillanceReport, REPORTS> tcas, Vector<SurveillanceReport, REPORTS> radar);

/*
 * Checks that all SurveillanceReports are in
 * exactly one Cluster.
 * Ran after all CorrelatedAircraft are
 * calculated by the algorithm.
 *
 * @return int 0 for success, 1 for error
 */
int check_cluster_count();

/*
 * Converts a Cluster to a CorrelationAircraft, calculate
 * correct location, heading, etc.
 * This means that this cluster has been determined
 * to be exactly one aircraft.
 *
 * @param cluster The cluster to convert
 * @return CDTIReport The generated report
 */
CorrelationAircraft convert_aircraft(Cluster cluster);

/*
 * Generates the distance between two SurveillanceReports
 * based on their speed, heading, and distance.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The distance metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float calc_distance(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    float distance = calcHeading(reportOne, reportTwo);
    distance += calcEuclidDistance(reportOne, reportTwo);
    distance += calcSpeed(reportOne, reportTwo);

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
float calcHeading(SurveillanceReport reportOne, SurveillanceReport reportTwo)
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
float calcEuclidDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo)
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
float calcSpeed(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    return 0;
}
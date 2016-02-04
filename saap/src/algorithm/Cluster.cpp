//
// Created by andrea on 1/19/16.
//

#include "../../inc/algorithm/Cluster.h"

//Collection<Cluster> clusters;
//Collection<SurveillanceReport> adsb;
//Collection<SurveillanceReport> radar;
//Collection<SurveillanceReport> tcas;
SurveillanceReport ownship;

/*
 * Main method of the correlation algorithm.
 * Called from the ReportReceiver.
 * Takes in all of the SurveillanceReports,
 * adds SurveillanceReports to all of the
 * possible Clusters for each SurveillanceReport,
 * generates Clusters, and evaluates each
 * detected aircraft location.
 *
 * return: int 0 for success, 1 for error
 */
//int correlate(SurveillanceReport ownship, Collection<SurveillanceReport> adsb,
//    Collection<SurveillanceReport> tcas, Collection<SurveillanceReport> radar);

/*
 * Checks that all SurveillanceReports are in
 * exactly one Cluster.
 * Ran after all CorrelatedAircraft are
 * calculated by the algorithm.
 *
 * return: int 0 for success, 1 for error
 */
int checkClusterCount();

/*
 * Converts a Cluster to a CorrelationAircraft, calculate
 * correct location, heading, etc.
 * This means that this cluster has been determined
 * to be exactly one aircraft.
 *
 * return: CDTIReport The generated report
 */
CorrelationAircraft convertAircraft(Cluster cluster);

/*
 * Generates the distance between two SurveillanceReports
 * based on their speed, heading, and distance.
 *
 * return: float The distance metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float calcDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    float distance = calcHeading(reportOne, reportTwo);
    distance += calcEuclidDistance(reportOne, reportTwo);
    distance += calcSpeed(reportOne, reportTwo);

    return distance;
}

float calcHeading(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    return 0;
}

float calcEuclidDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    return 0;
}

float calcSpeed(SurveillanceReport reportOne, SurveillanceReport reportTwo)
{
    return 0;
}
/**
* @file Cluster.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Calculates the distance matrices from three sets of input Surveillance
 * Reports and then generates the Clusters.
*/

#include <cmath>
#include <Categorizer.h>
#include "Cluster.h"
#include "CorrelationAircraft.h"

#define REPORTS 10

using namespace std;

vector<Cluster> clusters;
vector<CorrelationAircraft> corrAircraft;

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
int Correlate(vector<FlightReport>& adsb,
    vector<FlightReport>& tcas, vector<FlightReport>& radar) {

    //Create individual clusters for all ads-b reports
    for (int i = 0; i < adsb.size(); i++)
    {
       // clusters.push_back(0);
        adsb.at(i);
    }

    //for all tcas reports, run algorithm code (can be switched out)
    CompareReports(tcas);

    //for all radar reports, run code
    CompareReports(radar);

    //Checks that all SurveillanceReports are in only one Cluster
    if (CheckClusterCount())
    {
        printf("At least one SurveillanceReport is either not in a cluster or"
                       " in multiple clusters.\n");
    }

    //for every clusters, call ConvertAircraft(), add to corrAircraft
    for (int i = 0; i < clusters.size(); i++)
    {
        //ConvertAircraft();
    }

    Categorize(corrAircraft);

}

int ConvertAircraft(Cluster cluster) {
//device type needs to be the highest ranking type in the cluster
    //ads-b, tcas, radar

    //compare all fields of each report in cluster, create correlationAircraft
    //add to corrAircraft
}

int CompareReports(vector<FlightReport>& reports)
{
    //for each report
    //use algorithm
}

/*
 * Checks that all SurveillanceReports are in
 * exactly one Cluster.
 * Ran after all CorrelatedAircraft are
 * calculated by the algorithm.
 *
 * @return int 0 for success, 1 for error
 */
int CheckClusterCount() {
    return TRUE;
}

/*
 * Generates the distance between two SurveillanceReports
 * based on their speed, heading, and distance.
 *
 * @param reportOne The first report to compare
 * @param reportTwo The second report to compare
 * @return float The distance metric from 0 to 1 where 1 is the
 * highest correlation.
 */
float CalcDistance(FlightReport& reportOne, FlightReport& reportTwo)
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
float CalcHeading(FlightReport& reportOne, FlightReport& reportTwo)
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
float CalcEuclidDistance(FlightReport& reportOne, FlightReport&
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
float CalcSpeed(FlightReport& reportOne, FlightReport& reportTwo)
{
    return 0;
}
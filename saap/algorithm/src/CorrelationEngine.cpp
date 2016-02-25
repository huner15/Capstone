/**
* @file CorrelationEngine.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 2-23-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the interchangeable algorithms will be based on.
*/

#include <Categorizer.h>
#include "CorrelationEngine.h"
#include "SurveillanceReport.h"

using namespace std;

void CorrelationEngine::RunAlgorithm() {

}

CorrelationEngine::CorrelationEngine() {

}

CorrelationEngine::~CorrelationEngine() {

}

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
int Correlate(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,
        vector<SurveillanceReport *> *radar) {
    Cluster *cluster;

    _corr_aircraft.clear();
    _clusters.clear();

    // RunAlgorithm();

    //Create individual clusters for all ads-b reports
    for (int i = 0; i < adsb->size(); i++)
    {
        cluster = newCluster();
        cluster->adsb = adsb->at(i);
    }
    //Create individual clusters for all radar reports
    for (int i = 0; i < radar->size(); i++)
    {
        cluster = newCluster();
        cluster->radar = radar->at(i);
    }
    //Create individual clusters for all tcas reports
    for (int i = 0; i < tcas->size(); i++)
    {
        cluster = newCluster();
        cluster->tcas = tcas->at(i);
    }

    //Checks that all SurveillanceReports are in only one Cluster
    if (CheckClusterCount())
    {
        printf("At least one SurveillanceReport is either not in a cluster or"
                       " in multiple clusters.\n");
    }

    //for every cluster, call ConvertAircraft(), add to _corr_aircraft
    for (int i = 0; i < _clusters.size(); i++)
    {
        ConvertAircraft(_clusters.at(i));
        _free_clusters.push_back(_clusters.at(i));
    }

    Categorize(&_corr_aircraft);

    //Delete Correlate and Cluster data
    for (int i = 0; i < _corr_aircraft.size(); i++) {
        freeAircraft.push_back(_corr_aircraft.at(i));
    }

    _corr_aircraft.clear();
    _clusters.clear();

    return 0;

}

int ConvertAircraft(Cluster *cluster) {
    Device type;
    CorrelationAircraft *aircraft;

    //Set Device type based on the ranking: ads-b, tcas, radar
    if (cluster->adsb != NULL) {
        type = ADSB;
    }
    else if (cluster->tcas != NULL) {
        type = TCAS;
    }
    else if (cluster->radar != NULL) {
        type = RADAR;
    }
    else {
        printf("Trying to convert empty Cluster to CorrelationAircraft\n");
    }


    //Set prediction vectors
    //Velocity predictedVector, Velocity predictedLoc

//    std::time_t time, TailNumber tail_number, TcasID
//    tcas_id, RadarID radar_id, GeographicCoordinate geographic_coordinate,
//            SphericalCoordinate spherical_coordinate, Velocity velocity,

    aircraft = new CorrelationAircraft(type, );
    _corr_aircraft.push_back(aircraft);
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
    int result = 0;

    for (int i = 0; i < _clusters.size(); i++)
    {
        if (_clusters.at(i)->tcas == NULL & _clusters.at(i)->radar == NULL
            && _clusters.at(i)->adsb == NULL)
        {
            result = 1;
        }
    }

    return result;
}

/*
 * Gets an empty Cluster pointer from the existing list or
 * mallocs a new one.
 * @return Cluster * the pointer to the new Cluster to use
 */
Cluster *newCluster()
{
    Cluster *cluster;

    if (_free_clusters.empty()) {
        cluster = (Cluster *) malloc(sizeof(Cluster));
    }
    else {
        cluster = _free_clusters.at(_clusters.size() - 1);
        _free_clusters.pop_back();
    }

    cluster->adsb = NULL;
    cluster->radar = NULL;
    cluster->tcas = NULL;
    cluster->prediction = Velocity(0, 0, 0);

    return cluster;
}

/*
 * Gets an empty Cluster pointer from the existing list or
 * mallocs a new one.
 * @return Cluster * the pointer to the new Cluster to use
 */
CorrelationAircraft *newCorrAircraft()
{
    CorrelationAircraft *aircraft;

    if (_free_aircraft.empty()) {
        aircraft = (CorrelationAircraft *) malloc(sizeof(CorrelationAircraft));
    }
    else {
        aircraft = _free_aircraft.at(_free_aircraft.size() - 1);
        _free_aircraft.pop_back();
    }

    return aircraft;
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
float CalcDistance(FlightReport *reportOne, FlightReport *reportTwo)
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
float CalcHeading(FlightReport *reportOne, FlightReport *reportTwo)
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
float CalcEuclidDistance(FlightReport *reportOne, FlightReport *reportTwo)
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
float CalcSpeed(FlightReport *reportOne, FlightReport *reportTwo)
{
    return 0;
}
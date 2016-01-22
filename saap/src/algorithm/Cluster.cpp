//
// Created by andrea on 1/19/16.
//

#include "Cluster.h"

//Collection<Cluster> clusters;
//Collection<SurveillanceReport> adsb;
//Collection<SurveillanceReport> radar;
//Collection<SurveillanceReport> tcas;
SurveillanceReport ownship;

/*
 * Main method of the correlation algorithm.
 * Takes in all of the SurveillanceReports,
 * adds SurveillanceReports to all of the
 * possible Clusters for each SurveillanceReport,
 * generates Clusters, and evaluates each
 * detected aircraft location.
 *
 * return: int 0 for success, 1 for error
 */
int correlate(SurveillanceReport ownship);
    //Collection<SurveillanceReport> adsb
    //Collection<SurveillanceReport> tcas
    //Collection<SurveillanceReport> radar

/*
 * Generates possible clusters by creating
 * a Cluster with each possible SurveillanceReport
 * pairing based on the surveillance device
 * margins of error provided by General Atomics.
 *
 * return: int 0 for success, 1 for error
 */
int generatePossibleClusters();

/*
 * Calculates the location of the aircraft
 * represented by the given Cluster.
 *
 * return: CorrelationAircraft The represented
 * aircraft
 */
CorrelationAircraft calcLocation(Cluster cluster);

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
 * Checks that all Clusters have atleast one
 * SurveillanceReport and no more than one
 * SurveillanceReport of the same surveillance
 * device type (ADS-B, TCAS, and radar).
 *
 * return: int 0 for success, 1 for error
 */
int checkValidClusters();

/*
 * Converts a Cluster to a CorrelationAircraft so
 * it can be added to the current Snapshot.
 * This means that this cluster has been determined
 * to be exactly one aircraft.
 *
 * return: CDTIReport The generated report
 */
CorrelationAircraft convertAircraft(Cluster cluster);

/*
 * Compares two TCAS and ADS-B SurveillanceReports
 * to determine if they represent the same or two
 * different aircraft.
 * If two different aircraft are represented,
 * a new Cluster is added for the second aircraft.
 *
 * return: int 0 for success, 1 for error
 */
int compTA(SurveillanceReport tcas, SurveillanceReport adsb);

/*
 * Compares two radar and ADS-B SurveillanceReports
 * to determine if they represent the same or two
 * different aircraft.
 * If two different aircraft are represented,
 * a new Cluster is added for the second aircraft.
 *
 * return: int 0 for success, 1 for error
 */
int compRA(SurveillanceReport radar, SurveillanceReport adsb);

/*
 * Compares two TCAS and radar SurveillanceReports
 * to determine if they represent the same or two
 * different aircraft.
 * If two different aircraft are represented,
 * a new Cluster is added for the second aircraft.
 *
 * return: int 0 for success, 1 for error
 */
int compTR(SurveillanceReport tcas, SurveillanceReport radar);
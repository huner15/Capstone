/**
* @file Cluster.h
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Holds the Cluster struct and cluster correlation headers.
*/

#ifndef SAAS_CLUSTER_H
#define SAAS_CLUSTER_H

#include <stdint.h>
#include "FlightReport.h"
#include "CorrelationAircraft.h"
#include <vector>

#define TRUE 0
#define FALSE 1

using namespace std;

/**
 * A class representing one aircraft in the airspace.
 * All Surveillance Reports may not exist.
 */
class Cluster : public Cluster {
protected:
    /** Report from the TCAS hardware. */
    FlightReport *_tcas;
    /** Report from the ADS-B hardware. */
    FlightReport *_adsb;
    /** Report from the radar hardware. */
    FlightReport *_radar;
    /** Predicted aircraft location for the next second. */
    Velocity _prediction;
public:
    Cluster();

    ~Cluster();

    void SetRadar(FlightReport *radar);

    void SetADSB(FlightReport *adsb);

    void SetTCAS(FlightReport *tcas);
};

#endif //SAAS_CLUSTER_H
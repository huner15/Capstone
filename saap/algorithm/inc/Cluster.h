/**
* @file Cluster.h
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief Holds the Cluster struct and cluster correlation headers.
*/

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <stdint.h>
#include <vector>

#include "CorrelationAircraft.h"
#include "SurveillanceReport.h"

using namespace std;

/**
 * A class representing one aircraft in the airspace.
 * All Surveillance Reports may not exist.
 */
class Cluster {
public:
    /** Report from the TCAS hardware. */
    SurveillanceReport *_tcas;
    /** Report from the ADS-B hardware. */
    SurveillanceReport *_adsb;
    /** Report from the radar hardware. */
    SurveillanceReport *_radar;
    /** Predicted aircraft location for the next second. */
    Velocity _prediction;

    /**
     * Creates a new empty Cluster.
     */
    Cluster();

    /**
     * Deconstructs a new empty Cluster.
     */
    ~Cluster();

    /**
     * Sets the radar's report pointer.
     * @param radar the radar report pointer
     */
    void SetRadar(SurveillanceReport *radar);

    /**
     * Sets the adsb's report pointer.
     * @param adsb the radar report pointer
     */
    void SetADSB(SurveillanceReport *adsb);

    /**
     * Sets the tcas's report pointer.
     * @param radar the tcas report pointer
     */
    void SetTCAS(SurveillanceReport *tcas);
};

#endif

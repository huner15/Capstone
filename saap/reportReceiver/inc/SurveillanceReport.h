/**
* @file CorrelationAircraft.h
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a CorrelationAircraft and converts a Cluster into one
 * most likely CorrelationAircraft.
*/

#ifndef SAAS_CORRELATIONAIRCRAFT_H
#define SAAS_CORRELATIONAIRCRAFT_H

#include "Cluster.h"
#include "SurveillanceReport.h"
#include "Velocity.h"

using namespace std;

/**
 * A struct that represents an individual aircraft in the airspace around
 * the ownship. Holds the evaluated current location, heading, elevation,
 * and identifiers from the Surveillance Report or Surveillance Reports
 * that were evaluated to represent this aircraft.
 * All fields may not be populated.
 */
class SurveillanceReport {
protected:
    /**
     * An encapsulated Flight Report
     */
    FlightReport _flight_report;

    /*
     * Geographic location converted to Spherical coordinates.
     */
    GeographicCoordinate _converted_geographic;
public:
    SurveillanceReport();

    SurveillanceReport::SurveillanceReport(FlightReport flight_report);
};

#endif //SAAS_CORRELATIONAIRCRAFT_H

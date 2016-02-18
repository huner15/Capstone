/**
* @file SurveillanceReport.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a SurveillanceReport and converts a Cluster into one
 * most likely SurveillanceReport.
*/

#include <FlightReport.h>
#include "Cluster.h"
#include "SurveillanceReport.h"
#include "Velocity.h"
#include <ctime>

SurveillanceReport::SurveillanceReport(FlightReport flight_report) {
    _flight_report = flight_report;

    _converted_geographic = flight_report.get_geographic_coordinate();
}

SurveillanceReport::SurveillanceReport() {

}

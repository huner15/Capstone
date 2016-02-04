//
// Created by kevin on 1/31/16.
//

#ifndef SAAS_SIMULATIONFLIGHTSGENERATOR_H
#define SAAS_SIMULATIONFLIGHTSGENERATOR_H


#include "../../lib/util/inc/ActualFlights.h"


/**
 * SFG is constructed by taking in file name of flightscenario.  An instance of a FlightScenartio
 * is created, which is a composite of aircraft which is a composite of flightplans which
 * is a composite of flight legs.  Using this flightscenario the SFG will create an ActualFlighs class
 * which is a composite of Actual Flight which is a composite of actual reports.  The SFG will create
 * Actual Reports one by one by by time and information from the aircraft in the flightscenario class.
 *
 */
class SimulationFlightsGenerator {
public:

    SimulationFlightsGenerator(std::string flight_scenario_file_name);

    std::vector<ActualFlights> GenerateActualFlights();

    std::vector<SimulationFlights> GenerateSimulationFlights();

    ActualReport CreateActualReport();





};

#endif //SAAS_SIMULATIONFLIGHTSGENERATOR_H

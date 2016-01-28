//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_FLIGHTSCENARIOPROCESSOR_H
#define SAMPLEJSONCPP_FLIGHTSCENARIOPROCESSOR_H


#include "JsonIO.h"

/**
 * FlightScenarioIO is the utility library for reading and writing
 * regarding the Flight Scenario files.
 */

class FlightScenarioIO : public JsonIO {
public:

    /**
     * Reads the JSON FlightScenario file and returns a reference
     * to the root of the JSON file.
     * @return The root of the JSON File
     */
     static Json::Value ReadFile();

    /**
     * Accessor function to retrieve the initial Ownship data.
     * @return Initial Ownship data in Json::Value form.
     */
    static Json::Value GetAbsoluteOwnshipData();

    /**
     * Accessor function for the list of flight plans.
     * @return All the flight plans in the JSON in JSon::Value form.
     */
    static Json::Value GetFlightPlans();

    /**
     * Accessor method to a vector containing the starting positions of all aircrafts.
     * @return Vector containing the starting positions of all aircrafts
     */
    static std::vector<std::vector<int>> GetStartPositions();

    /**
     * Accesor method to all the flight legs.
     * @return A vector containing all the flight legs in the flight scenario.
     */
    static std::vector<Json::Value> GetFlightLegs();

    /**
     * Write specified Json::Value to a formatted output log file.
     * @param value is the Json::Value that you want to log.
     */
    static void WriteFile(Json::Value value);
};

#endif //SAMPLEJSONCPP_FLIGHTSCENARIOPROCESSOR_H

//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_ACTUALFLIGHTSIO_H
#define SAMPLEJSONCPP_ACTUALFLIGHTSIO_H

#include "JsonIO.h"


/**
 * ActualFlightsIO is the utility library for reading and writing
 * regarding the ActualFlights file.
 */
class ActualFlightsIO : public JsonIO {
public:

    /**
     * Reads the JSON ActualFLights file and returns a reference
     * to the root of the JSON file.
     * @return The root of the JSON File
     */
    static Json::Value ReadFile();

    /**
     * Reads the JSON ActualFlights file and returns JSON Value
     * of Actual Flights.
     * @return JSON value of Actual Flights
     */
    static Json::Value GetActualFlights();

    /**
     * Gets a Vector containing all actual reports in the file.
     * @return vector containing all the actual reports in Json::Value form.
     */
    static std::vector<Json::Value> GetActualReports();

    /**
     * TODO
     */
    virtual void writeFile(Json::Value value);
};


#endif //SAMPLEJSONCPP_ACTUALFLIGHTSIO_H

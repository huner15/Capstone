//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H
#define SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

#include "JsonIO.h"

class SimulationFlightsIO : public JsonIO {
public:

    static Json::Value readFile();

    static Json::Value getSimulationFlights();

    static std::vector<Json::Value> getAllADSBReports();

    static std::vector<Json::Value> getAllTCASReports();

    static std::vector<Json::Value> getAllRadarReports();

    static std::vector<Json::Value> getALlOwnshipReports();

    virtual void writeFile(Json::Value value);
};


#endif //SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

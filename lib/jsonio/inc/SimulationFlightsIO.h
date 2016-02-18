//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H
#define SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

#include "JsonIO.h"

class SimulationFlightsIO : public JsonIO {
private:
    static Json::Value OpenFile(std::string file_name);

    static Flight ReadFlightData(std::string file_name);
public:

    static FlightSimulation ReadFile(std::string file_name);

    static Json::Value GetFlights(std::string file_name);

    static std::vector<Json::Value> GetAllADSBReports();

    static std::vector<Json::Value> GetAllTCASReports();

    static std::vector<Json::Value> GetAllRadarReports();

    static std::vector<Json::Value> GetALlOwnshipReports();

    virtual void writeFile(Json::Value value);
};


#endif //SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

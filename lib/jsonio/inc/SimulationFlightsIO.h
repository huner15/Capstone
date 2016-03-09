//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H
#define SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

#include "JsonIO.h"
#include "Flight.h"
#include "FlightSimulation.h"
#include "SaasUtil.h"

class SimulationFlightsIO : public JsonIO {
private:
    static Json::Value OpenFile(std::string file_name);

    static FlightSimulation ReadFlightData(std::string file_name);

public:

    static FlightSimulation ReadFile(std::string file_name);

    static Json::Value GetSimulationFlights();

    static Json::Value GetReports(std::string file_name);

    static Json::Value GetAllADSBReports();

    static Json::Value GetAllTCASReports();

    static Json::Value GetAllRadarReports();

    static Json::Value GetAllOwnshipReports();

    static AdsBReport SetAdsBReportData(std::time_t time, double latitude,
                                        double longitude, double altitude,
                                        std::string tail_number,
                                        double north, double east, double down);

    static RadarReport SetRadarReportData(std::time_t time, double range,
                                          double azimuth,
                                          double elevation, uint16_t radar_id,
                                          double latitude,
                                          double longitude, double altitude,
                                          double north, double east,
                                          double down);

    static TcasReport SetTcasReportData(uint8_t tcas_id, double range,
                                        double altitude, double bearing);

    static OwnshipReport SetOwnshipReportData(std::time_t time, double latitude,
                                              double longitude, double altitude,
                                              double north, double east,
                                              double down);

    virtual void writeFile(Json::Value value);
};


#endif //SAMPLEJSONCPP_SIMULATIONFLIGHTSIO_H

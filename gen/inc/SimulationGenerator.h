/*
 * SimulationGenerator.h
 * Specific Atomics
 * Kevin Pham
 * 2-28-16
 * Driver for creating SimulationFlights File
 */

#ifndef SIMULATIONGENERATOR_H_
#define SIMULATIONGENERATOR_H_

#include "FlightScenario.h"
#include "FlightScenarioIO.h"
#include <ctime>
#include "TcasID.h"
#include "RadarID.h"
#include <math.h>

class SimulationGenerator {
private:
    FlightScenario _flight_scenario;
    std::vector<Velocity> _ownship_velocities;
    std::vector<double> _ownship_bearings;
    std::vector<GeographicCoordinate> _ownship_positions;

public:
    SimulationGenerator() {};
    SimulationGenerator(std::string file_name);
    ~SimulationGenerator() {};

    Json::Value FormatOwnshipReport(std::time_t time, double altitude,
                                    double latitude, double longitude,
                                    double north, double east, double down,
                                    int index);

    Json::Value FormatAdsbReport(TailNumber tail_number ,std::time_t time,
                                 double altitude, double latitude,
                                 double longitude,
                                 double north, double east, double down,
                                int index);

    Json::Value FormatTcasReport(TcasID id, double altitude, double bearing,
                                 double range,int index);


    Json::Value FormatRadarReport(RadarID id ,std::time_t time, double range,
                                  double azimuth, double elevation,
                                  double altitude, double latitude,
                                  double longitude,
                                  double north, double east, double down,
                                  int index);


    Json::Value WriteOwnshipReports();

    Json::Value WriteAdsbReports();

    Json::Value WriteTcasReports();

    Json::Value WriteRadarReports();

    Json::Value WriteReports();
};


#endif //SAAS_SIMULATIONGENERATOR_H

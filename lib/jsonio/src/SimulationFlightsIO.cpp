//
// Created by KEVIN on 11/27/2015.
//

#include <FlightSimulation.h>
#include "SimulationFlightsIO.h"

using namespace std;

Json::Value SimulationFlightsIO::OpenFile(std::string file_name) {
    Json::Value root;   // will contain the root value after parsing.
    Json::Reader reader;
    std:string file_dir = "../../lib/jsonio/src/";
    std::string file = file_dir + file_name;
    std::ifstream test(file, std::ifstream::binary);
    bool parsing_successful = reader.parse(test, root, false);

    if (!parsing_successful) {
        // report to the user the failure and their locations in the document.
        std::cout << reader.getFormattedErrorMessages()
        << "\n";
        return Json::nullValue;
    }
    else {
        return root;
    }
}

FlightSimulation SimulationFlightsIO::ReadFile(std::string file_name) {

}

//TODO: Fix Time
Flight SimulationFlightsIO::ReadFlightData(std::string file_name) {
    Json::Value all_flights = GetFlights(file_name);
    std::vector<FlightReport> all_flight_reports;

    for(int i = 0; i < all_flights.size(); i++) {
        Json::Value json_report = all_flights[i]["flight"]["flightReport"];
        Json::Value json_geo_coord = json_report["geographicCoordinate"];
        Json::Value json_sphr_coord = json_report["sphericalCoordinate"];
        Json::Value json_velocity = json_report["velocity"];

        TailNumber tail (json_report["tailNumber"].asString());
        TcasID tcas_id (json_report["tcasID"].asUInt());
        RadarID radar_id (json_report["radarID"].asUInt());
        GeographicCoordinate geo_coord (json_geo_coord["latitude"].asDouble(),
                                    json_geo_coord["longitude"].asDouble(),
                                    json_geo_coord["altitude"].asDouble());
        SphericalCoordinate sphr_coord (json_sphr_coord["range"].asDouble(),
                                        json_sphr_coord["elavation"].asDouble(),
                                        json_sphr_coord["azimuth"].asDouble());
        Velocity velocity (json_velocity["east"].asDouble(),
                           json_velocity["down"].asDouble(),
                           json_velocity["north"].asDouble());
        Device device (RADAR);
        FlightReport report (std::time(nullptr), tail, tcas_id, radar_id,
                                geo_coord, sphr_coord, velocity, device);

        all_flight_reports.push_back(report);
    }

    Flight flight (all_flight_reports);
    return flight;
}

Json::Value SimulationFlightsIO::GetFlights(std::string file_name) {
    Json::Value root = OpenFile(file_name);

    return root["flightSimulation"];
}


Json::Value SimulationFlightsIO::GetSimulationFlights() {
    return Json::nullValue;
}

std::vector<Json::Value> SimulationFlightsIO::GetAllADSBReports() {
    Json::Value simFlights = GetSimulationFlights();
    std::vector<Json::Value> adsbReports;

    for ( int index = 0; index < simFlights.size(); index++ ) {
        adsbReports.push_back(simFlights[index]["adsbReport"]);
    }

    return adsbReports;
}

std::vector<Json::Value> SimulationFlightsIO::GetAllTCASReports() {
    Json::Value simFlights = GetSimulationFlights();
    std::vector<Json::Value> tcasReports;

    for ( int index = 0; index < simFlights.size(); index++ ) {
        tcasReports.push_back(simFlights[index]["tcasReport"]);
    }

    return tcasReports;

}

std::vector<Json::Value> SimulationFlightsIO::GetAllRadarReports() {
    Json::Value simFlights = GetSimulationFlights();
    std::vector<Json::Value> radarReports;

    for ( int index = 0; index < simFlights.size(); index++ ) {
        radarReports.push_back(simFlights[index]["radarReport"]);
    }

    return radarReports;
}

std::vector<Json::Value> SimulationFlightsIO::GetALlOwnshipReports() {
    Json::Value simFlights = GetSimulationFlights();
    std::vector<Json::Value> ownReports;

    for ( int index = 0; index < simFlights.size(); index++ ) {
        ownReports.push_back(simFlights[index]["ownshipReport"]);
    }

    return ownReports;
}

void SimulationFlightsIO::writeFile(Json::Value value) {
    std::ofstream file_id;
    file_id.open("SimulationFlightOutput", fstream::out);

    Json::Value output;
    //output["value"] = root["val1"].asInt() + root["val2"].asInt();

    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value("ROME"));
    vec.append(Json::Value(true));

    output["array"] = vec;
    //root["output"] = output;

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(value);

    file_id.close();
}
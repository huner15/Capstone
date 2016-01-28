//
// Created by KEVIN on 11/27/2015.
//

#include "SimulationFlightsIO.h"

using namespace std;

Json::Value SimulationFlightsIO::ReadFile() {
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream test("../../lib/jsonio/src/SimulationFlightInput.json", std::ifstream::binary);
    //test.close();
    bool parsingSuccessful = reader.parse(test, root, false);
    if (!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout << reader.getFormattedErrorMessages()
        << "\n";
        return Json::nullValue;
    }
    else {
        return root;
    }
}

Json::Value SimulationFlightsIO::GetSimulationFlights() {
    Json::Value root = ReadFile();

    return root["simulationFlights"];
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
//
// Created by KEVIN on 11/27/2015.
//

#include "FlightScenarioIO.h"

using namespace std;


Json::Value FlightScenarioIO::ReadFile() {
    Json::Value root;   // will contain the root value after parsing.
    Json::Reader reader;
    std::ifstream test("../../lib/jsonio/src/FlightScenarioInput.json", std::ifstream::binary);
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

Json::Value FlightScenarioIO::GetAbsoluteOwnshipData() {
    Json::Value root = ReadFile();

    return root["absoluteOwnship"];
}

Json::Value FlightScenarioIO::GetFlightPlans() {
    Json::Value root = ReadFile();

    return root["flightPlans"];
}

std::vector<std::vector<int>> FlightScenarioIO::GetStartPositions() {
    Json::Value flight_plans = GetFlightPlans();
    std::vector<int> position;
    std::vector<std::vector<int>> positions;

    for (int index = 0; index < flight_plans.size(); index++ ) {
        position.push_back(flight_plans[index]["startPosition"]["x"].asInt());
        position.push_back(flight_plans[index]["startPosition"]["y"].asInt());
        position.push_back(flight_plans[index]["startPosition"]["z"].asInt());
        positions.push_back(position);
        position.empty();
    }

    return positions;
}

std::vector<Json::Value> FlightScenarioIO::GetFlightLegs() {
    Json::Value flight_plans = GetFlightPlans();
    std::vector<Json::Value> flight_legs;

    for ( int index = 0; index < flight_plans.size(); index++ ) {
        flight_legs.push_back(flight_plans[index]["flightLegs"]);
    }

    return flight_legs;
}

void FlightScenarioIO::WriteFile(Json::Value value) {
    std::ofstream file_id;

    file_id.open("FlightScenarioOutput", fstream::out);
    Json::StyledWriter styled_writer;
    file_id << styled_writer.write(value);

    file_id.close();
}


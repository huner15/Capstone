//
// Created by KEVIN on 11/27/2015.
//

#include "ActualFlightsIO.h"

using namespace std;

Json::Value ActualFlightsIO::ReadFile() {
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream test("FlightScenarioOutput", std::ifstream::binary);
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

Json::Value ActualFlightsIO::GetActualFlights() {
    Json::Value root = readFile();

    return root["actualFlight"];
}

std::vector<Json::Value> ActualFlightsIO::GetActualReports() {
    Json::Value actual_flights = GetActualFlights();

    return std::vector<Json::Value>
            (std::begin(actual_flights["actualReport"]), std::end(actual_flights["actualReport"]));
}

void ActualFlightsIO::writeFile(Json::Value value) {
    std::ofstream file_id;
    file_id.open("ActualFlightOutput", fstream::out);

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
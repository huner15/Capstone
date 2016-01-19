//
// Created by KEVIN on 11/27/2015.
//

#include "FlightScenarioIO.h"

using namespace std;


Json::Value FlightScenarioIO::readFile() {
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream test("../../lib/jsonio/src/FlightScenarioInput.json", std::ifstream::binary);
    //test.close();
    bool parsingSuccessful = reader.parse(test, root, false);
    if (!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout << reader.getFormatedErrorMessages()
        << "\n";
        return Json::nullValue;
    }
    else {
        return root;
    }
}

Json::Value FlightScenarioIO::getAbsoluteOwnshipData() {
    Json::Value root = readFile();

    return root["absoluteOwnship"];
}

Json::Value FlightScenarioIO::getFlightPlans() {
    Json::Value root = readFile();

    return root["flightPlans"];
}

std::vector<std::vector<int>> FlightScenarioIO::getStartPositions() {
    Json::Value flightPlans = getFlightPlans();
    std::vector<int> position;
    std::vector<std::vector<int>> positions;

    for ( int index = 0; index < flightPlans.size(); index++ ) {
        position.push_back(flightPlans[index]["startPosition"]["x"].asInt());
        position.push_back(flightPlans[index]["startPosition"]["y"].asInt());
        position.push_back(flightPlans[index]["startPosition"]["z"].asInt());
        //std::cout << flightPlans[index]["startPosition"]["x"];


        positions.push_back(position);
        position.empty();
    }

    return positions;
}

std::vector<Json::Value> FlightScenarioIO::getFlightLegs() {
    Json::Value flightPlans = getFlightPlans();
    std::vector<Json::Value> flightLegs;


    for ( int index = 0; index < flightPlans.size(); index++ ) {
        flightLegs.push_back(flightPlans[index]["flightLegs"]);
    }

    return flightLegs;
}



void FlightScenarioIO::writeFile(Json::Value value) {
    std::ofstream file_id;
    file_id.open("FlightScenarioOutput", fstream::out);

    Json::Value output;
    //output["value"] = root["val1"].asInt() + root["val2"].asInt();

    Json::Value vec(Json::arrayValue);
    //vec.append(Json::Value(1));
    //vec.append(Json::Value("ROME"));
    //vec.append(Json::Value(true));

    //output["array"] = vec;

    Json::Value plans = value["flightPlans"];
    Json::Value test;

    for ( int index = 0; index < plans.size(); index++ ) {
        int num = plans[index]["flightLegs"].size();
        //cout << plans[index]["flightLegs"];
        for( Json::ValueIterator itr = plans[index]["flightLegs"].begin() ; itr != plans[index]["flightLegs"].end() ; itr++ ) {
            test[index] = (*itr);
        }
    }
    //cout << "Hi";

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(test);

    file_id.close();
}


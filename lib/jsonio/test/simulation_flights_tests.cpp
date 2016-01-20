//
// Created by kevin on 1/20/16.
//

#include <SimulationFlightsIO.h>

int main() {

    Json::Value tcas = SimulationFlightsIO::getAllTCASReports().front();

    Json::StyledWriter style;
    std::cout << style.write(tcas);
    return 0;
}
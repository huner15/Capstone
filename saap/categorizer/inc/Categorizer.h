/**
 * @file Categorizer.cpp
 * @author Specific Atomics
 * @authors Michael Lenz, Frank Poole
 * @date 4-14-16
 * @brief TODO: Description
 */

#ifndef SAAS_CATEGORIZER_H_
#define SAAS_CATEGORIZER_H_

#include <cmath>

#include <cdti.pb.h>

#include "ClientSocket.h"
#include "CorrelationAircraft.h"
#include "SpecialMath.h"
#include "FlightReport.h"

class Categorizer {

private:
    ClientSocket& _client_socket;

public:
    Categorizer(ClientSocket& _client_socket);

    ~Categorizer();

    void Categorize(std::vector<CorrelationAircraft *> *aircraft);

    double CalculateRange(CDTIPlane plane);

    double CalculateCPA(CDTIPlane plane);

    CDTIPlane_Severity CategorizePlane(CDTIPlane plane);

    std::vector<CDTIPlane> MakeCDTI(
            std::vector<CorrelationAircraft*>* aircraft);

    CDTIPlane MakeCDTIPlane(CorrelationAircraft* aircraft);
};

#endif

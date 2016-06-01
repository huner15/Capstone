/*
 * @file FakeCorrelator.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 5-30-16
 * @brief Implements the functionality of a FakeCorrelator.
 */

#include "Device.h"
#include "FakeCorrelator.h"

std::vector<CorrelationAircraft *> *FakeCorrelator::Correlate(
        ReceivedReports receivedReports) {
    std::vector<CorrelationAircraft *> *correlatedAircraft =
            new std::vector<CorrelationAircraft *>;
    std::vector<SurveillanceReport *> *radarReports = receivedReports.GetRadar();

    for (auto const &surveillanceReport: *radarReports) {
        correlatedAircraft->push_back(new CorrelationAircraft(
                surveillanceReport->GetTime(),
                surveillanceReport->GetTailNumber(),
                surveillanceReport->GetTcasID(),
                surveillanceReport->GetRadarID(),
                *(surveillanceReport->GetGeographicCoordinate()),
                *(surveillanceReport->GetSphericalCoordinate()),
                *(surveillanceReport->GetVelocity()),
                *(surveillanceReport->GetVelocity()),
                *(surveillanceReport->GetGeographicCoordinate()),
                RADAR));
    }

    return correlatedAircraft;
}

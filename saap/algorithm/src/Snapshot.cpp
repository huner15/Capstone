/**
* @file Snapshot.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 2-24-16
* @brief Represents the layout of the airspace during one evaluation of the Correlation Engine.
*/

#include <CorrelationAircraft.h>
#include <Snapshot.h>

Snapshot::Snapshot(std::vector<CorrelationAircraft> *aircraft, std::time_t timestamp) {
    _aircraft = aircraft;
    _timestamp = timestamp;
}

Snapshot::Snapshot() {

}

Snapshot::~Snapshot() {

}

std::vector<CorrelationAircraft> *Snapshot::GetAircraft() const {
    return _aircraft;
}

std::time_t Snapshot::GetTimestamp() const {
    return _timestamp;
}

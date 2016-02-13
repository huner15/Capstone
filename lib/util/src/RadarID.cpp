/*
 * @file RadarID.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Contains implementation of Radar ID functions.
 */

#include "RadarID.h"

RadarID::RadarID() {
    _radar_id = (uint16_t) (rand() % UINT16_MAX);
}

RadarID::RadarID(uint16_t radar_id) {
    _radar_id = radar_id;
}

RadarID::~RadarID() {
}

uint16_t RadarID::Get() {
    return _radar_id;
}

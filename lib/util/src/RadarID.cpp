/*
 * RadarID.cpp
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#include "RadarID.h"

RadarID::RadarID() {
    //srand (time(NULL));
    //_radar_id = rand() % UINT16_MAX;
}

RadarID::RadarID(uint16_t radar_id) {
    _radar_id = radar_id;
}

RadarID::~RadarID() {

}

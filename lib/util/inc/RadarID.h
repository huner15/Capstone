/*
 * RadarID.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef RADAR_ID_H_
#define RADAR_ID_H_

#include <stdint.h>

class RadarID {
private:
    uint16_t _radar_id;

public:
    RadarID(uint16_t radar_id);

    ~RadarID();
};

#endif

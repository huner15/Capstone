/*
 * RadarID.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-13-16
 *
 */

#ifndef RADAR_ID_H_
#define RADAR_ID_H_

#include <cstdlib>
#include <stdint.h>

class RadarID {
private:
    uint16_t _radar_id;

public:
    /**
     * Create a RadarID with a randomly generated identifier between 0 and
     * 65535.
     */
    RadarID();

    /**
     * Create a RadarID with the specified identifier.
     */
    RadarID(uint16_t radar_id);

    /**
     * Deconstruct a RadarID.
     */
    ~RadarID();
};

#endif

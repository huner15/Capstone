/*
 * @file RadarID.h
 * @author Specific Atomics
 * @authors Kevin Pham, Frank Poole
 * @date 2-13-16
 * @brief Radar ID models the identifier assigned to an object by a radar
 * device upon object detection.
 */

#ifndef RADAR_ID_H_
#define RADAR_ID_H_

#include <stdint.h>
#include <cstdlib>
#include <ctime>

/**
 * Radar ID models the identifier assigned to an object by a radar
 * device upon object detection. If a specific number is not input during
 * assignment, a valid identification number will be generated.
 */
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
     * Create a RadarID with the specified identifier using an integer between 0
     * and 65535. If the specified integer is larger than 65535, construction
     * will proceed with the equivalent overflow integer value.
     */
    RadarID(uint16_t radar_id);

    /**
     * Deconstruct a RadarID.
     */
    ~RadarID();

    /**
     * Return the radar identification.
     */
    uint16_t Get() const;
};

#endif

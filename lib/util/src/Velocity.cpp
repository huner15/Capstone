/*
 * @file Velocity.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Implements functionality of Velocity.
 */

#include "Velocity.h"

Velocity::Velocity() {
    east = 0;
    down = 0;
    north = 0;
}

Velocity::Velocity(double east, double down, double north) {
    this->east = east;
    this->down = down;
    this->north = north;
}

Velocity Velocity::operator- (const Velocity& other) {
    return Velocity(this->east - other.east,
                    this->down - other.down,
                    this->north - other.north);
}

Velocity Velocity::operator+ (const Velocity& other) {
    return Velocity(this->east + other.east,
                    this->down + other.down,
                    this->north + other.north);
}

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

Velocity::Velocity(double e, double d, double n) {
    east = e;
    down = d;
    north = n;
}

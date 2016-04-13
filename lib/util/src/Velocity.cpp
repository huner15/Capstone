/*
 * @file Velocity.cpp
 * @author Specific Atomics
 * @authors Frank Poole Andrea Savage
 * @date 3-6-16
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

Velocity *Velocity::Average(Velocity *one, Velocity *two, Velocity
*three) {
    double east = 0, down = 0, north = 0, count = 0;
    double vOne, vTwo, vThree, removeVal;
    std::vector<Velocity *> velocities;

    if (one != NULL) {
        count++;
        velocities.push_back(one);
    }
    if (two != NULL) {
        count++;
        velocities.push_back(two);
    }
    if (three != NULL) {
        count++;
        velocities.push_back(three);
    }

    for (int i = 0; i < count; i++) {
        east += velocities.at(i)->east;
        down += velocities.at(i)->down;
        north += velocities.at(i)->north;
    }

    //Remove outlier if have all three velocities and it exists
    if (count == 3) {
        vOne = cbrt(pow(velocities.at(0)->east, 2) +
            pow(velocities.at(0)->down, 2) + pow(velocities.at(0)->north, 2));
        vTwo = cbrt(pow(velocities.at(1)->east, 2) +
            pow(velocities.at(1)->down, 2) + pow(velocities.at(1)->north, 2));
        vThree = cbrt(pow(velocities.at(2)->east, 2) +
            pow(velocities.at(2)->down, 2) + pow(velocities.at(2)->north, 2));

        //if difference is twice as big as other distance, must be an outlier
        removeVal = (fabs(vOne - vTwo) >= 2 * fabs(vTwo - vThree)) ? 0 : -1;
        removeVal += (fabs(vTwo - vThree) >= 2 * fabs(vThree - vOne)) ? 1 : -1;
        removeVal += (fabs(vThree - vOne) >= 2 * fabs(vOne - vTwo)) ? 2 : -1;

        if (removeVal != -1) {
            count--;
            east -= velocities.at(removeVal)->east;
            down -= velocities.at(removeVal)->down;
            north -= velocities.at(removeVal)->north;
        }
    }

    //No Velocities exist
    if (count == 0)
    {
        return NULL;
    }

    //geometric mean
    east = pow(east, 1 / count);
    down = pow(down, 1 / count);
    north = pow(north, 1 / count);

    return new Velocity(east, down, north);
}

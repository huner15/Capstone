/*
 * @file Velocity.cpp
 * @author Specific Atomics
 * @authors Frank Poole Andrea Savage
 * @date 3-6-16
 * @brief Implements functionality of Velocity.
 */

#include "Velocity.h"

Velocity::Velocity() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Velocity::Velocity(double east, double down, double north) {
    this->x = east;
    this->y = down;
    this->z = north;
}

double Velocity::East() const {
    return this->x;
}

double Velocity::Down() const {
    return this->y;
}

double Velocity::North() const {
    return this->z;
}

void Velocity::SetEast(double east) {
    this->x = east;
}

void Velocity::SetDown(double down) {
    this->y = down;
}

void Velocity::SetNorth(double north) {
    this->z = north;
}

Velocity Velocity::operator- (const Velocity& other) {
    return Velocity(this->East() - other.East(),
                    this->Down() - other.Down(),
                    this->North() - other.North());
}

Velocity Velocity::operator+ (const Velocity& other) {
    return Velocity(this->East() + other.East(),
                    this->Down() + other.Down(),
                    this->North() + other.North());
}

Velocity Velocity::Average(Velocity *one, Velocity *two, Velocity *three) {
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

    for (uint i = 0; i < count; i++) {
        east += velocities.at(i)->East();
        down += velocities.at(i)->Down();
        north += velocities.at(i)->North();
    }

    //Remove outlier if have all three velocities and it exists
    if (count == 3) {
        vOne = cbrt(pow(velocities.at(0)->East(), 2) +
            pow(velocities.at(0)->Down(), 2) +
                            pow(velocities.at(0)->North(), 2));
        vTwo = cbrt(pow(velocities.at(1)->East(), 2) +
            pow(velocities.at(1)->Down(), 2) +
                            pow(velocities.at(1)->North(), 2));
        vThree = cbrt(pow(velocities.at(2)->East(), 2) +
            pow(velocities.at(2)->Down(), 2) +
                              pow(velocities.at(2)->North(), 2));

        //if difference is twice as big as other distance, must be an outlier
        removeVal = (fabs(vOne - vTwo) >= 2 * fabs(vTwo - vThree)) ? 1 : 0;
        removeVal += (fabs(vTwo - vThree) >= 2 * fabs(vThree - vOne)) ? 2 : 0;
        removeVal += (fabs(vThree - vOne) >= 2 * fabs(vOne - vTwo)) ? 3 : 0;

        if (removeVal != 0) {
            count--;
            east -= velocities.at(removeVal - 1)->East();
            down -= velocities.at(removeVal - 1)->Down();
            north -= velocities.at(removeVal - 1)->North();
        }
    }

    //No Velocities exist
    if (count == 0) {
        return Velocity(0, 0, 0);
    }

    //geometric mean
    east = east / (count + 1);
    down = down / (count + 1);
    north = north / (count + 1);

    return Velocity(east, down, north);
}

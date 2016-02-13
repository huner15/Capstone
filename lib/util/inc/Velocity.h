/*
 * @file Velocity.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief TODO:Description
 */

#include "Vector.h"

class Velocity : public Vector3D {
private:
public:
    double North();

    union {
        std::array<double, 2> array;
        struct {
            double north, east, down;
        };
    };
};

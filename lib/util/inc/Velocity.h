/*
 * @file Velocity.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Velocity represents the three dimensional velocity of a physical
 * object.
 */

#include "Vector.h"

/**
 * Velocity represents the three dimensional velocity of a physical object.
 * Allows for accessing velocity dimensions using the keywords north, east, and
 * down.
 */
class Velocity : public Vector3D {
private:
public:
    /**
     * Enable accessing the underlying three dimensional vector using the
     * keywords north, east, and down instead or x, y, z or array indexing.
     */
    union {
        std::array<double, 3> array;
        struct {
            double north, east, down;
        };
    };

    /**
     * Create a new velocity with east, down, and north velocities of zero.
     */
    Velocity();

    /**
     * Create a new velocity with the specified east, down, and north
     * velocities.
     * @param east the eastwards velocity
     * @param down the downwards velocity
     * @param north the northwards velocity
     */
    Velocity(double east, double down, double north);
};

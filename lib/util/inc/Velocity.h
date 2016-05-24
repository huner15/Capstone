/**
 * @file Velocity.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Velocity represents the three dimensional velocity of a physical
 * object.
 */

#ifndef VELOCITY_H_
#define VELOCITY_H_

#include "Vector.h"
#include <vector>
#include <cmath>

/**
 * Velocity represents the three dimensional velocity of a physical object.
 * Allows for accessing velocity dimensions using the keywords north, east, and
 * down.
 */
class Velocity : public Saas_Util::Vector3D {
private:
public:
    /**
     * Enable accessing the underlying three dimensional vector using the
     * keywords north, east, and down instead or x, y, z or array indexing.
     */
    union {
        std::array<double, 3> array;
        struct {
            double east, down, north;
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

    /**
     * Create a velocity representing the relative velocity of this velocity to
     * another velocity.
     * @param other the velocity to compare against
     * @return a relative velocity
     */
    Velocity operator- (const Velocity& other);

    /**
     * Create a velocity representing the relative velocity of this velocity to
     * another velocity.
     * @param other the velocity to compare against
     * @return a relative velocity
     */
    Velocity operator+ (const Velocity& other);

    static Velocity Average(Velocity *one, Velocity *two, Velocity *three);
};

#endif

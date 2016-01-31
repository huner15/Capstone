/*
 * Vector.h
 * Specific Atomics
 * Frank Poole
 * 1-30-16
 * Vector is a wrapper class for std::array which allows for public field access
 * using the fields x, y z, and w.
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdint>
#include <array>

/**
 * A vector represents an array of type T for a fixed size N. While the
 * underlying array operations and mechanics use std::array, the Vector class
 * acts as a wrapper to allow for more readable vector field access using the
 * dimensions x, y, z, and w appropriately for 2D, 3D, and 4D floating point
 * vectors. Note that the public array member may be accessed externally to
 * access underlying std::array functions. Vector is an aggregate class. A 3D
 * vector may be initialized using the syntax Vector3D vector = {x, y, z}, where
 * x, y, and z are floating point values. If less than the full number of
 * arguments is added when constructing a vector, the remaining floating point
 * values will be initialized to zero. Vector math operations may be added
 * to Vector as needed.
 * @tparam T the vector element type
 * @tparam N the fixed size of the vector
 */
template<typename T, std::size_t N>
struct vector {
    /** An array of fixed size. */
    std::array<T, N> array;
};

/**
 * Two dimensional floating point vector specialization. Provides access to the
 * underlying array using the fields x and y.
 */
template<>
struct vector<double, 2> {
    union {
        std::array<double, 2> array;
        struct {
            double x, y;
        };
    };
};

/**
 * Three dimensional floating point vector specialization. Provides access to
 * the underlying array using the fields x, y, and z.
 */
template<>
struct vector<double, 3> {
    union {
        std::array<double, 3> array;
        struct {
            double x, y, z;
        };
    };
};

/**
 * Four dimensional floating point vector specialization. Provides access to
 * the underlying array using the fields x, y, z, and w.
 */
template<>
struct vector<double, 4> {
    union {
        std::array<double, 4> array;
        struct {
            double x, y, z, w;
        };
    };
};

/**
 * Type definition for a two dimensional vector. Prefer using Vector2D to using
 * the underlying Vector<double, 2>.
 */
typedef vector<double, 2> Vector2D;

/**
 * Type definition for a three dimensional vector. Prefer using Vector3D to
 * using the underlying Vector<double, 3>.
 */
typedef vector<double, 3> Vector3D;

/**
 * Type definition for a four dimensional vector. Prefer using Vector4D to
 * using the underlying Vector<double, 4>.
 */
typedef vector<double, 4> Vector4D;

#endif

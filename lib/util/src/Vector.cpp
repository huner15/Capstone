/*
 * Vector.cpp
 * Specific Atomics
 * Frank Poole
 * 1-30-16
 * Vector implements all functions defined in Vector.h. Add additional operator
 * overloads and math function implementations here if needed.
 */

#include "Vector.h"

template<typename T, std::size_t N>
size_t Vector<T, N>::Size() {
    return array.size();
}

/*
 * @file Vector.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-13-16
 * @brief Vector implements all functions defined in Vector.h. Add additional
 * operator overloads and math function implementations here if needed.
 */

#include "Vector.h"

template<typename T, std::size_t N>
size_t Vector<T, N>::Size() {
    return array.size();
}

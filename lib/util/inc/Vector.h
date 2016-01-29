/*
 * Vector.h
 * Specific Atomics
 * Frank Poole
 * 1-28-16
 * TODO: Description
 */

#ifndef SAAS_VECTOR3_H_
#define SAAS_VECTOR3_H_

template<typename T, int n>
class Vector {
public:
    T data[n];
};

typedef Vector<double, 2> vec2;
typedef Vector<double, 3> vec3;
typedef Vector<double, 4> vec4;

typedef Vector<int, 2> int2;
typedef Vector<int, 3> int3;
typedef Vector<int, 4> int4;

#endif //SAAS_VECTOR3_H

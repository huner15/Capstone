/*
 * ActualReport.h
 * Specific Atomics
 * Frank Poole
 * 1-31-16
 * TODO: Decription
 */

#ifndef ACTUAL_REPORT_H_
#define ACTUAL_REPORT_H_

#include <ctime>

#include "TailNumber.h"
#include "IntruderID.h"
#include "GeographicCoordinate.h"
#include "SphericalCoordinate.h"
#include "Vector.h"

class ActualReport {
private:
    std::time_t time;
    TailNumber tailNumber;
    IntruderID intruderID;
    GeographicCoordinate geographicCoordinate;
    SphericalCoordinate sphericalCoordinate;
    Vector3D velocity;
public:
};

#endif

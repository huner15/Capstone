/**
 * @file Categorizer.cpp
 * @author Specific Atomics
 * @authors Michael Lenz, Frank Poole
 * @date 4-14-16
 * @brief Generate a CDTI Report assigning every detected aircraft it's own
 * proximate traffic severity category.
 */

#ifndef CATEGORIZER_H_
#define CATEGORIZER_H_

#include <cmath>

#include <cdti.pb.h>

#include "ClientSocket.h"
#include "CorrelationAircraft.h"
#include "SpecialMath.h"

class Categorizer {

private:
    /** Create a single ownship cdti plane as the ownship is the system origin
     * and it's field values do not update. */
    CDTIPlane* _ownship_cdti_plane;

    /** Generate a constant CDTI plane to represent ownship. */
    CDTIPlane* CreateOwnshipCDTIPlane();

    /** Calculate the range from ownship to a given CDTI plane. */
    double CalculateRange(CDTIPlane plane);

    /** Calculate the closest point of approach to a given CDTI plane. */
    double CalculateCPA(CDTIPlane plane);

    /** Generate the severity category for a given CDTI plane. */
    CDTIPlane_Severity GenerateSeverity(CDTIPlane* plane);

public:
    /** Create a new Categorizer. */
    Categorizer();

    /** Deconstruct the Categorizer. */
    ~Categorizer();

    /** Generate a CDTI Report assigning every detected aircraft it's own
     * proximate traffic severity category. */
    CDTIReport* Categorize(std::vector<CorrelationAircraft *> *aircraft);
};

#endif

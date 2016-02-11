//
// Created by michael on 2/6/16.
//


#include <bits/stl_bvector.h>
#include <cmath>
#include <cdti.pb.h>
#include "../../../../.CLion12/system/cmake/generated/d5e848c9/d5e848c9/Debug/lib/gp/capstone-shared/cdti.pb.h"
#include "../../../lib/util/inc/Vector.h"


double calculateRange(CDTIPlane plane);
double calculateCPA(CDTIPlane plane);
void CategorizePlane(CDTIPlane plane);
/*
 * Call to begin categorization
 * TODO set what this takes to wahtever comes out of the algorith
 */
void categorize(){
    std::vector<CDTIPlane>* planes = new std::vector<CDTIPlane>();
    //call something to translate whatever is given into a list of CDTIplanes
    for(int i = 0; i < planes->size(); i++){
        CategorizePlane(planes->[i]);
    }
}
/**
 * desides where to Categorize a plane
 */
void CategorizePlane(CDTIPlane plane){
    double range = calculateRange(plane);
    double cpa = calculateCPA(plane);
    if(range < 2 && abs(plane.position().z) < 300 && cpa < .5)
        plane.set_severity(plane.RESOLUTION);
    else if(range < 5 && abs(plane.position().z) < 500 && cpa < 1)
        plane.set_severity(plane.TRAFFIC);
    else if(range < 10 && abs(plane.position().z) < 1000)
        plane.set_severity(plane.PROXIMATE);
    else
        plane.set_severity(NULL);

}


/**
 * calculates range to ownship.
 * returns a double representing the planes distance to the ownship
 */
double calculateRange(CDTIPlane plane) {
    Vector pos = plane.position();
    return std::sqrt(pos.x*pos.x + pos.y*pos.y);

}
/**
 * calculates closest point of approach
 * returns a double representing the closest point of approach.
 */
double calculateCPA(CDTIPlane plane) {
    //since ownship is at (0,0) formula is |c|/sqrt(a^2+b^2)
    double a, b, c;
    a = plane.velocity().x;
    b = plane.velocity().y;
    c = plane.position().x *(plane.position().y + plane.velocity().y)
        - (plane.position().x + plane.velocity().x) - plane.velocity().y;
    return abs(c)/sqrt(a*a + b*b);
}






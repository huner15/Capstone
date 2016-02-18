/*
 * SpecialMath.cpp
 * Specific Atomics
 * Michael Lenz
 * 2-15-16
 * does specialty math
*/


#include "SpecialMath.h"

#define dot(u,v) ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)

namespace SpecialMath {
    template<typename T, std::size_t N>
    double DistanceFormula(Saas_Util::Vector<T, N> a, Saas_Util::Vector<T, N> b)
    {
        double toReturn = 0;
        for(int i = 0; i < N; i ++)
        {
            double square = a.array[i] - b.array[i];
            toReturn += square * square;
        }
        return sqrt(toReturn);

    }

    double LineDistance(Saas_Util::Vector<double, 3> pointOnLine,Saas_Util::Vector<double, 3> directionOfLine,
                        Saas_Util::Vector<double, 3> referencePoint){
        Saas_Util::Vector<double, 3> v = directionOfLine;
        Saas_Util::Vector<double, 3> w;
        w.x = referencePoint.x - pointOnLine.x;
        w.y = referencePoint.y - pointOnLine.y;
        w.z = referencePoint.z - pointOnLine.z;

        double c1 = dot(w, v);
        double c2 = dot(v, v);
        double b = c1/c2;

        v.x = pointOnLine.x + b*v.x;
        v.y = pointOnLine.y + b*v.y;
        v.z = pointOnLine.z + b*v.z;
        w.x = referencePoint.x;
        w.y = referencePoint.y;
        w.z = referencePoint.z;
        return DistanceFormula<double, 3>(w, v);
    }

}
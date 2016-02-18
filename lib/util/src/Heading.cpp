/*
 * @file Heading.cpp
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief TODO write description
 */

#include "Heading.h"

Heading::Heading(double azimuth, double elevation) {
    _azimuth = azimuth;
    _elevation = elevation;
}

double Heading::getAzimuth() {
    return _azimuth;
}

double Heading::getElevation() {
    return _elevation;
}
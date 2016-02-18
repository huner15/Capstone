/*
 * @file Heading.h
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief TODO write description
 */

#ifndef SAAS_HEADING_H
#define SAAS_HEADING_H


class Heading {
public:
    Heading(){};
    Heading(double azimuth, double elevation);

    double getAzimuth();
    double getElevation();

private:
    double _azimuth;
    double _elevation;
};


#endif //SAAS_HEADING_H

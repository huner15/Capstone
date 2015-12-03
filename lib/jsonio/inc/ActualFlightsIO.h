//
// Created by KEVIN on 11/27/2015.
//

#ifndef SAMPLEJSONCPP_ACTUALFLIGHTSIO_H
#define SAMPLEJSONCPP_ACTUALFLIGHTSIO_H

#include "JsonIO.h"

class ActualFlightsIO : public JsonIO {
public:

    virtual Json::Value readFile();

    virtual void writeFile(Json::Value value);
};


#endif //SAMPLEJSONCPP_ACTUALFLIGHTSIO_H

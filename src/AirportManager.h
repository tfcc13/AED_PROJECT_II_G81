//
// Created by tiago on 19-12-2023.
//

#ifndef PROJECT_II_AIRPORTMANAGER_H
#define PROJECT_II_AIRPORTMANAGER_H

#include "Graph.h"
#include "Airport.h"
#include "Script.h"
class AirportManager {



private:
    Script& script_;
public:
    AirportManager(Script &script);
    int getAirportFlightsNumber(const string& airport);

};


#endif //PROJECT_II_AIRPORTMANAGER_H

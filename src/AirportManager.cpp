//
// Created by tiago on 19-12-2023.
//

#include "AirportManager.h"

AirportManager::AirportManager(Script& script) : script_(script) {}

int AirportManager::getAirportFlightsNumber(const string &airport) {

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));

    if(airportVert == NULL) return -1;

    return airportVert->getAdj().size();


}


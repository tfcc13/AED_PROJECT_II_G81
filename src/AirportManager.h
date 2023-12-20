//
// Created by tiago on 19-12-2023.
//

#ifndef PROJECT_II_AIRPORTMANAGER_H
#define PROJECT_II_AIRPORTMANAGER_H

#include "Graph.h"
#include "Airport.h"
#include "Script.h"
#include <iomanip>

class Script;

class AirportManager {



private:
    Script& script_;
public:
    AirportManager(Script &script);
    int getAirportFlightsNumber(const string& airport);
    int getAirportAirlinesNumber(const string& airport);
    const set<string> getCitiesSet(const string& airport) const;
    const set<string> getAirlinesSet(const string& airport) const;
    const set<Airport>getAirportsSet(const string& airport) const;
    int getDestinationCitiesNumber(const string& airport);
    const string& getAirportName(const string& airport) const;
    void getDestinationCitiesNames(const string& airport) const;
    void getAirlinesNames(const string& airport) const;
    int getDestinationAirportsNumber(const string& airport);
    void getDestinationAirportsNames(const string& airport);

};


#endif //PROJECT_II_AIRPORTMANAGER_H

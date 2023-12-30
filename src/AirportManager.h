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
    int getAirportFlightsNumber(const string& airport_name);
    int getAirportAirlinesNumber(const string& airport_name);
    set<string> getCitiesSet(const string& airport_name) const;
    set<string> getAirlinesSet(const string& airport_name) const;
    set<Airport>getAirportsSet(const string& airport_name) const;
    int getDestinationCitiesNumber(const string& airport_name);
    const string& getAirportName(const string& airport_name) const;
    void getDestinationCitiesNames(const string& airport_name) const;
    void PrintAirlinesNames(const string& airport_name) const;
    int getDestinationAirportsNumber(const string& airport_name);
    void getDestinationAirportsNames(const string& airport_name) const;
    void getAirportsFlightsData(const string& airport_name) const;
    int getDestinationCountriesNumber(const string& airport_name) const;
    set<string>getDestinationCountriesSet(const string& airport_name) const;
    void getDestinationCountriesNames(const string& airport_name) const;

};

#endif //PROJECT_II_AIRPORTMANAGER_H

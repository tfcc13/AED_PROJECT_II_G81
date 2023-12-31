#ifndef PROJECT_II_AIRPORTMANAGER_H
#define PROJECT_II_AIRPORTMANAGER_H

#include "Graph.h"
#include "Airport.h"
#include "Script.h"
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>

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
    vector<pair<Airport,int>> getTopKAiportTrafficCap(int k) const ;
    void printAllAirports() const;
    set<Airport> airportArticulationPoints();
    void dfs_art(Graph<Airport> &g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);
    int getAirportsNumber() const;
    int getAirlinesNumber() const;
    set<string> getCitiesInCountryWithAirport(const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCityAndCountry(const string& city, const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCountry(const string& country) const;
    int getNumberOfFlightsInAirline(const string& airline) const;

};

#endif //PROJECT_II_AIRPORTMANAGER_H

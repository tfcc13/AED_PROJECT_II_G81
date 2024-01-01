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
    /**
     *Class constructor
     * @param script Reference to the used script
     */
    AirportManager(Script &script);

    /**
     *
     * @param airport_name Given airport code/name
     * @return number of flights of a given Airport
     */
    int getAirportFlightsNumber(const string& airport_name, const string& departures_or_arrivals);

    /**
     *
     * @param airport_name Given airport code/name
     * @return number of airlines in a given Airport
     */
    int getAirportAirlinesNumber(const string& airport_name, const string& departures_or_arrivals);

    /**
     *
     * @param airport_name Given airport code/name
     * @return set of direct reachable cities from an Airport
     */
    set<string> getCitiesSet(const string& airport_name, const string& departures_or_arrivals) const;

    /**
     *
     * @param airport_name Given airport code/name
     * @return set of Airlines operating in a given Airport
     */
    set<string> getAirlinesSet(const string& airport_name, const string& departures_or_arrivals) const;

    /**
     *
     * @param airport_name Given airport code/name
     * @return  set of direct reachable Airports from a given Airport
     */
    set<Airport>getAirportsSet(const string& airport_name) const;

    int getAirportsNumber() const;
    int getAirlinesNumber() const;
    int getFlightsNumber() const;
    int getCitiesNumber() const;
    int getCountriesNumber() const;
    set<string> getCitiesInCountry(const string& country);
    int getDestinationCitiesNumber(const string& airport_name, const string& departures_or_arrivals);
    const string& getAirportName(const string& airport_name) const;
    void getDestinationCitiesNames(const string& airport_name, const string& departures_or_arrivals) const;
    void printAirlinesNames(const string& airport_name, const string& departures_or_arrivals) const;
    int getDestinationAirportsNumber(const string& airport_name);
    void getDestinationAirportsNames(const string& airport_name) const;
    void getAirportsFlightsData(const string& airport_name, const string& departures_or_arrivals) const;
    int getDestinationCountriesNumber(const string& airport_name, const string& departures_or_arrivals) const;
    set<string>getDestinationCountriesSet(const string& airport_name, const string& departures_or_arrivals) const;
    void getDestinationCountriesNames(const string& airport_name, const string& departures_or_arrivals) const;
    vector<pair<Airport,int>> getTopKAiportTrafficCap(int k) const ;
    void printAllAirports() const;
    set<Airport> airportArticulationPoints();
    void dfs_art(Graph<Airport> &g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);

    set<string> getCitiesInCountryWithAirport(const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCityAndCountry(const string& city, const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCountry(const string& country) const;
    int getNumberOfFlightsInAirline(const string& airline) const;
    set<pair<string, string>> getReachableAirports(const string &airport_name, int max_stops);
    set<string> getReachableCountries(const string& airport_name, int max_stops);
    set<pair<string, string>> getReachableCities(const string& airport_name, int max_stops);
    Vertex<Airport> *const findClosestAirport(const position &targetPosition) const;
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTrip();
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTripDiameter();
    int airportsDistanceBFSVisit(const Graph<Airport>& g, Vertex<Airport>* v1, Vertex<Airport>*& v2);

};

#endif //PROJECT_II_AIRPORTMANAGER_H

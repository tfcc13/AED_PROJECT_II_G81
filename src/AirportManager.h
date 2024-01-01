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

using destToSrcStopsPair = pair<pair<Vertex<Airport> *, Vertex<Airport> *>, int>;


class AirportManager {

private:
    Script& script_;

public:

    /// Class constructor
    /// \param script Reference to the used script
    AirportManager(Script &script);

    /// Finds the number of outgoing and incoming flights
    ///**Time Complexity:** O(1)
    /// @param airport_name Given airport code/name
    /// \return number of flights of a given Airport
    int getAirportFlightsNumber(const string& airport_name);

    /// Finds the number of Airlines Operating in a given Airport
    ///**Time Complexity:** O(1)
    /// \param airport_name Given airport code/name
    /// \return number of airlines in a given Airport
    int getAirportAirlinesNumber(const string& airport_name);

    /// Makes a set of destination cities available from an Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    ///\return set of direct reachable cities from an Airport
    set<string> getCitiesSet(const string& airport_name) const;

    /// Makes a set of Airlines Operating in a given Airport
    ///**Time Complexity:** O(|E|+|E|)
    /// \param airport_name Given airport code/name
    ///\return set of Airlines operating in a given Airport
    set<string> getAirlinesSet(const string& airport_name) const;

    /// Makes a set of destination Airports
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return  set of direct reachable Airports from a given Airport
    set<Airport>getAirportsSet(const string& airport_name) const;

    /// Finds the number of destination cities available in a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return  number of destination cities
    int getDestinationCitiesNumber(const string& airport_name);

    /// Searches for an Airport name
    ///**Time Complexity:** O(1)
    /// \param airport_name Given airport code/name
    /// \return  the name of the Airport
    const string& getAirportName(const string& airport_name) const;

    /// Prints destination cities available from an Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    void getDestinationCitiesNames(const string& airport_name) const;

    /// Prints the Airlines Operating in a given Airport
    ///**Time Complexity:** O(|E|+|E|)
    /// \param airport_name Given airport code/name
    void printAirlinesNames(const string& airport_name) const;

    /// Finds the number of destination Airports from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return number of reachable Airports from a given Airport
    int getDestinationAirportsNumber(const string& airport_name);

    /// Prints the destination Airports from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    void getDestinationAirportsNames(const string& airport_name) const;

    /// Prints the flights data available from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    void getAirportsFlightsData(const string& airport_name) const;

    /// Finds the number of destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return the number of direct reachable countries from a given Airport
    int getDestinationCountriesNumber(const string& airport_name) const;

    /// Finds the destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return set of direct reachable countries from a given Airport
    set<string>getDestinationCountriesSet(const string& airport_name) const;

    /// Prints the destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
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
    set<Airport> getReachableAirports(const string &airport_name, int max_stops);
    set<string> getReachableCountries(const string& airport_name, int max_stops);
    set<pair<string, string>> getReachableCities(const string& airport_name, int max_stops);
    Vertex<Airport> *const findClosestAirport(const position &targetPosition) const;
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTrip();
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTripDiameter();
    int airportsDistanceBFSVisit(const Graph<Airport>& g, Vertex<Airport>* v1, Vertex<Airport>*& v2,   vector<destToSrcStopsPair>& res, int maxD);
};

#endif //PROJECT_II_AIRPORTMANAGER_H

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
    int getAirportFlightsNumber(const string& airport_name, const string& departures_or_arrivals);

    /// Finds the number of Airlines Operating in a given Airport
    ///**Time Complexity:** O(1)
    /// \param airport_name Given airport code/name
    /// \return number of airlines in a given Airport
    int getAirportAirlinesNumber(const string& airport_name, const string& departures_or_arrivals);

    /// Makes a set of destination cities available from an Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    ///\return set of direct reachable cities from an Airport
    set<string> getCitiesSet(const string& airport_name, const string& departures_or_arrivals) const;

    /// Makes a set of Airlines Operating in a given Airport
    ///**Time Complexity:** O(|E|+|E|)
    /// \param airport_name Given airport code/name
    ///\return set of Airlines operating in a given Airport
    set<string> getAirlinesSet(const string& airport_name, const string& departures_or_arrivals) const;

    /// Makes a set of destination Airports
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return  set of direct reachable Airports from a given Airport
    set<Airport>getAirportsSet(const string& airport_name) const;

    /// Gets the number of existent Airports in the network
    /// \return number of airports
    int getAirportsNumber() const;

    /// Gets the number of existent Airlines in the network
    /// \return number of airlines
    int getAirlinesNumber() const;
    int getFlightsNumber() const;
    int getCitiesNumber() const;
    int getCountriesNumber() const;
    set<string> getCitiesInCountry(const string& country);

    /// Finds the number of destination cities available in a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return  number of destination cities
    int getDestinationCitiesNumber(const string& airport_name, const string& departures_or_arrivals);

    /// Searches for an Airport name
    ///**Time Complexity:** O(1)
    /// \param airport_name Given airport code/name
    /// \return  the name of the Airport
    const string& getAirportName(const string& airport_name) const;

    /// Prints destination cities available from an Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    void getDestinationCitiesNames(const string& airport_name, const string& departures_or_arrivals) const;

    /// Prints the Airlines Operating in a given Airport
    ///**Time Complexity:** O(|E|+|E|)
    /// \param airport_name Given airport code/name
    void printAirlinesNames(const string& airport_name, const string& departures_or_arrivals) const;

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
    void getAirportsFlightsData(const string& airport_name, const string& departures_or_arrivals) const;

    /// Finds the number of destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return the number of direct reachable countries from a given Airport
    int getDestinationCountriesNumber(const string& airport_name, const string& departures_or_arrivals) const;

    /// Finds the destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    /// \return set of direct reachable countries from a given Airport
    set<string>getDestinationCountriesSet(const string& airport_name, const string& departures_or_arrivals) const;

    /// Prints the destination countries  from a given Airport
    ///**Time Complexity:** O(|E|)
    /// \param airport_name Given airport code/name
    void getDestinationCountriesNames(const string& airport_name, const string& departures_or_arrivals) const;

    int getFlightsPerCity(const string& city, const string& country) const;
    int getFlightsPerAirline(const string& airline) const;

    /// Finds the Airports with the greatest air traffic capacity
    ///**Time Complexity:** O(|V|)
    /// \param k  number of Airports  to list
    /// \return vector of pairs of Airports and the number of their flights
    vector<pair<Airport,int>> getTopKAiportTrafficCap(int k) const ;

    /// Prints all airports
    ///**Time Complexity:** O(|V|)
    void printAllAirports() const;

    /// Finds the Airports important to the network capability
    ///**Time Complexity:** O(|V|+|E|)
    /// \return set of Airports that are important to the network capability
    set<Airport> airportArticulationPoints();

    /// Auxiliary function to check if removing an Airport creates an extra component
    ///**Time Complexity:** O(|V|+|E|)
    /// \param v current airport doing a DFS
    /// \param s auxiliary stack to keep track of the vertices in the current component
    /// \param l set of Airports that are articulation points
    /// \param i index of the vertex on the search
    void dfs_art(Graph<Airport> &g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);

    set<string> getCitiesInCountryWithAirport(const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCityAndCountry(const string& city, const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCountry(const string& country) const;
    int getNumberOfFlightsInAirline(const string& airline) const;
    set<pair<string, string>> getReachableAirports(const string &airport_name, int max_stops);
    set<string> getReachableCountries(const string& airport_name, int max_stops);
    set<pair<string, string>> getReachableCities(const string& airport_name, int max_stops);
    Vertex<Airport> *const findClosestAirport(const position &targetPosition) const;

    /// Finds the pair of airports with the most flight stops in a trip
    ///**Time Complexity:** O(|V|*(|V|+|E|))
    /// \return a vector with the pairs of airports with most flight stops in a trip
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTrip();

    /// Finds the pair of airports with the most distance between them (network diameter)
    ///**Time Complexity:** O(|V|*(|V|+|E|)+O|V|)
    /// \return a vector with a pair of a pair of airports with the most distance between them and the distance
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTripDiameter();

    /// Auxiliary function to get the maximum distance between Airports and the pair of their source and destination
    ///**Time Complexity:** O(|V|*(|V|+|E|)+O|V|)
    /// \param g network Airport graph
    /// \param v1 source vertex of the BFS
    /// \param v2 vertex to keep track of the last visited Airport
    /// \param res vector with a pair of a pair of airports with the most distance between them and the distance
    /// \param maxD variable to keep track of the current maximum distance between two vertices
    int airportsDistanceBFSVisit(const Graph<Airport>& g, Vertex<Airport>* v1, Vertex<Airport>*& v2,   vector<destToSrcStopsPair>& res, int maxD);
};

#endif //PROJECT_II_AIRPORTMANAGER_H

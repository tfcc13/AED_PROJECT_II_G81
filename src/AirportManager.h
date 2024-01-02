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

    /// Gets the number of existent flights in the network
    ///**Time Complexity:** O(1)
    /// \return number of flights
    int getFlightsNumber() const;

    /// Gets the number of existent cities in the network
    ///**Time Complexity:** O(n)
    /// \return number of cities
    int getCitiesNumber() const;

    /// Gets the number of existent countries in the network
    ///**Time Complexity:** O(1)
    /// \return number of countries
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

    /// Finds the cities within a given country
    ///**Time Complexity:** O(1)
    /// \param country country being searched
    /// \return a set of the cities in a given country
    set<string> getCitiesInCountryWithAirport(const string& country) const;

    /// Finds the airports within a given city and country
    ///**Time Complexity:** O(1)
    /// \param city being being searched
    /// \param country country being searched
    /// \return a vector of the airports in a given city and country
    vector<Vertex<Airport>*> getAirportsPerCityAndCountry(const string& city, const string& country) const;

    /// Finds the airports in a given country
    ///**Time Complexity:** O(1)
    /// \param country country being searched
    /// \return a vector of the airports in a given country
    vector<Vertex<Airport>*> getAirportsPerCountry(const string& country) const;

    /// Finds the number of flights in a given airline
    ///**Time Complexity:** O(1)
    /// \param airline airline being searched
    /// \return the number of flights in a given airline
    int getNumberOfFlightsInAirline(const string& airline) const;

    /// Finds the reachable airports from a given airport within a range of x stops
    ///**Time Complexity:** O(|V|+|E|)
    /// \param airport_name source airport
    /// \param max_stops range of the distance travelled
    /// \return set of reachable airports within the given range
    set<pair<string, string>> getReachableAirports(const string &airport_name, int max_stops);

    /// Finds the reachable countries from a given airport within a range of x stops
    ///**Time Complexity:** O(|V|+|E|)
    /// \param airport_name source airport
    /// \param max_stops range of the distance travelled
    /// \return set of reachable countries within the given range
    set<string> getReachableCountries(const string& airport_name, int max_stops);

    /// Finds the reachable cities from a given airport within a range of x stops
    ///**Time Complexity:** O(|V|+|E|)
    /// \param airport_name source airport
    /// \param max_stops range of the distance travelled
    /// \return set of reachable cities within the given range
    set<pair<string, string>> getReachableCities(const string& airport_name, int max_stops);

    ///Finds the closest airport to a given position
    ///**Time Complexity:** O(n)
    ///\param targetPosition Position (coordinates in latitude and longitude)
    ///\return Pointer to vertex of airport that's closest to targetPosition
    Vertex<Airport> *const findClosestAirport(const position &targetPosition) const;

    /// Finds the pair of airports with the most flight stops in a trip
    /// **Time Complexity:** O(|V|*(|V|+|E|))
    /// \return a vector with the pairs of airports with most flight stops in a trip
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTrip();

    /// Finds the pair of airports with the most distance between them (network diameter)
    /// **Time Complexity:** O(|V|*(|V|+|E|)+O|V|)
    /// \return a vector with a pair of a pair of airports with the most distance between them and the distance
    vector<pair<pair<Vertex<Airport>*,Vertex<Airport>*>,int>> getMaximumTripDiameter();

    /// Auxiliary function to get the maximum distance between Airports and the pair of their source and destination
    /// **Time Complexity:** O(|V|*(|V|+|E|)+O|V|)
    /// \param g network Airport graph
    /// \param v1 source vertex of the BFS
    /// \param v2 vertex to keep track of the last visited Airport
    /// \param res vector with a pair of a pair of airports with the most distance between them and the distance
    /// \param maxD variable to keep track of the current maximum distance between two vertices
    int airportsDistanceBFSVisit(const Graph<Airport>& g, Vertex<Airport>* v1, Vertex<Airport>*& v2,   vector<destToSrcStopsPair>& res, int maxD);


    ///Prints a group of paths
    ///**Time Complexity:** O(m*k) (where m is the number of paths and k is the average number of edges in a path)
    ///\param paths Vector that stores paths, in the form of vectors containing the edges that make the path.
    ///\param vertex Vertex from which the paths begin
    void printPaths(vector<vector<Edge<Airport>>> paths, Vertex<Airport> *vertex);





    ///Prints the shortest paths from a given airport to another.
    ///**Time Complexity:** O(|V|+|E|)
    ///\param depAirportCode Departure Airport Code
    ///\param destAirportCode Destination Airport Code
    void shortestAirportToAirport(string depAirportCode, string destAirportCode);

    ///Prints the shortest paths from a given airport to a city.
    ///**Time Complexity:** O(|V|+|E|)
    ///\param depAirportCode Departure Airport Code
    ///\param city Destination City
    ///\param country That city's country
    void shortestAirportToCity(string depAirportCode, string city, string country);

    ///Prints the shortest paths from a given airport to a position.
    ///**Time Complexity:** O(|V|+|E|)
    ///\param depAirportCode Departure Airport Code
    ///\param lat Destination Latitude
    ///\param lon Destination Longitude
    void shortestAirportToPosition(string depAirportCode, double lat, double lon);

    ///Prints the shortest paths from a given city to an airport.
    ///**Time Complexity:**O(n×(∣V∣+∣E∣))
    ///\param city Departure City
    ///\param country That city's country
    ///\param destAirportCode Destination Airport Code
    void shortestCityToAirport(string city, string country, string destAirportCode);

    ///Prints the shortest paths from a given city to another.
    /// **Time Complexity:**O(m×n×(∣V∣+∣E∣))
    ///\param depCity Departure City
    ///\param depCountry Departure City's country
    ///\param destCity Destination City
    ///\param destCountry Destination City's country
    void shortestCityToCity(string depCity, string depCountry, string destCity, string destCountry);

    ///Prints the shortest paths from a given city to a position.
    /// **Time Complexity:**O(n×(∣V∣+∣E∣))
    ///\param city Departure city
    ///\param country That city's country
    ///\param lat Destination Latitude
    ///\param lon Destination Longitude
    void shortestCityToPosition(string city, string country, double lat, double lon);

    ///Prints the shortest paths from a given position to an airport.
    /// **Time Complexity:**O(|V|+|E|)
    ///\param lat Departure Latitude
    ///\param lon Departure Longitude
    ///\param destAirportCode Destination Airport Code
    void shortestPositionToAirport(double lat, double lon, string destAirportCode);

    ///Prints the shortest paths from a given position to a city.
    /// **Time Complexity:**O(|V|+|E|)
    ///\param lat Departure Latitude
    ///\param lon Departure Longitude
    ///\param city Destination City
    ///\param country That city's country
    void shortestPositionToCity(double lat, double lon, string city, string country);

    ///Prints the shortest paths from a given position to another.
    /// **Time Complexity:**O(|V|+|E|)
    ///\param lat1 Departure Latitude
    ///\param lon1 Departure Longitude
    ///\param lat2 Destination Latitude
    ///\param lon2 Destination Longitude
    void shortestPositionToPosition(double lat1, double lon1, double lat2, double lon2);

    /// Prints the shortest paths from a given airport to another, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param depAirportCode Departure Airport Code
    /// \param destAirportCode Destination Airport Code
    /// \param filter Set of airlines that can be in the path
    void shortestAirportToAirport_Filter(string depAirportCode, string destAirportCode, unordered_set<string> filter);

    /// Prints the shortest paths from a given airport to a city, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param depAirportCode Departure Airport Code
    /// \param city Destination City
    /// \param country That city's country
    /// \param filter Set of airlines that can be in the path
    void shortestAirportToCity_Filter(string depAirportCode, string city, string country, unordered_set<string> filter);

    /// Prints the shortest paths from a given airport to a position, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param depAirportCode Departure Airport Code
    /// \param lat Destination Latitude
    /// \param lon Destination Longitude
    /// \param filter Set of airlines that can be in the path
    void shortestAirportToPosition_Filter(string depAirportCode, double lat, double lon, unordered_set<string> filter);

    /// Prints the shortest paths from a given city to an airport, through a limited set of airlines.
    /// **Time Complexity:**O(n×(∣V∣+∣E∣))
    /// \param city Departure City
    /// \param country That city's country
    /// \param destAirportCode Destination Airport Code
    /// \param filter Set of airlines that can be in the path
    void shortestCityToAirport_Filter(string city, string country, string destAirportCode, unordered_set<string> filter);

    /// Prints the shortest paths from a given city to another, through a limited set of airlines.
    /// **Time Complexity:**O(m×n×(∣V∣+∣E∣))
    /// \param depCity Departure City
    /// \param depCountry Departure City's country
    /// \param destCity Destination City
    /// \param destCountry Destination City's country
    /// \param filter Set of airlines that can be in the path
    void shortestCityToCity_Filter(string depCity, string depCountry, string destCity, string destCountry, unordered_set<string> filter);

    /// Prints the shortest paths from a given city to a position, through a limited set of airlines.
    /// **Time Complexity:**O(n×(∣V∣+∣E∣))
    /// \param city Departure city
    /// \param country That city's country
    /// \param lat Destination Latitude
    /// \param lon Destination Longitude
    /// \param filter Set of airlines that can be in the path
    void shortestCityToPosition_Filter(string city, string country, double lat, double lon, unordered_set<string> filter);

    /// Prints the shortest paths from a given position to an airport, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param lat Departure Latitude
    /// \param lon Departure Longitude
    /// \param destAirportCode Destination Airport Code
    /// \param filter Set of airlines that can be in the path
    void shortestPositionToAirport_Filter(double lat, double lon, string destAirportCode, unordered_set<string> filter);

    /// Prints the shortest paths from a given position to a city, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param lat Departure Latitude
    /// \param lon Departure Longitude
    /// \param city Destination City
    /// \param country That city's country
    /// \param filter Set of airlines that can be in the path
    void shortestPositionToCity_Filter(double lat, double lon, string city, string country, unordered_set<string> filter);

    /// Prints the shortest paths from a given position to another, through a limited set of airlines.
    /// **Time Complexity:**O(|V|+|E|)
    /// \param lat1 Departure Latitude
    /// \param lon1 Departure Longitude
    /// \param lat2 Destination Latitude
    /// \param lon2 Destination Longitude
    /// \param filter Set of airlines that can be in the path
    void shortestPositionToPosition_Filter(double lat1, double lon1, double lat2, double lon2, unordered_set<string> filter);

};

#endif //PROJECT_II_AIRPORTMANAGER_H

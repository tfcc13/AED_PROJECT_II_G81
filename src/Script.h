#ifndef PROJECT_II_SCRIPT_H
#define PROJECT_II_SCRIPT_H

#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include "Graph.h"
#include "AirportManager.h"

using namespace std;

static string airportsCSV  = "../dataset/airports.csv";

static string airlinesCSV  = "../dataset/airlines.csv";

static string flightsCSV  = "../dataset/flights.csv";

struct FlightHash {
    size_t operator()(const Flight& flight) const {
        return flight(flight);
    }
};

struct FlightEqual {
    bool operator()(const Flight& flight1, const Flight& flight2) const {
        return flight1 == flight2;
    }
};

class AirportManager;

class Script {

private:
    string script_;
    unordered_map<string, Vertex<Airport>*> all_airports_;
    unordered_map<string, Airline> all_airlines_;
    unordered_set<Flight, FlightHash, FlightEqual> all_flights_;
    unordered_map<string, set<string>> cities_per_country_;
    unordered_map<string, unordered_map<string, vector<Vertex<Airport>*>>> airports_per_city_and_country_;
    Graph<Airport> airportGraph_;

    friend class AirportManager;

public:
    /// Script constructor
    /// \param script name of the generated script class
    Script(const string& script);

    /// Loads the data from provided  csv files
    ///
    void loadDataset(const string& airports, const string& airlines, const string& flights);

    ///Populates all_airports_
    ///**Time Complexity:** O(1)
    /// \param airports file with the airports data
    void loadAirports(const string& airports);

    ///Populates all_airlines_
    ///**Time Complexity:** O(1)
    /// \param airlines file with the airlines data
    void loadAirlines(const string& airlines);

    ///Populates all_flights_
    ///**Time Complexity:** O(1)
    /// \param flights file with the flights data
    void loadFlights(const string& flights);

/*
    ///Getter function of all_airports_
    /// \return all_airports_
    unordered_map<string, Airport> getAirportsMap() const;
*/

/*
    ///Getter function of all_airlines_
    /// \return all_airports_
    set<Airline> getAirlinesSet() const;
*/

    ///Getter function of all_flights_
    /// \return all_flights_
    unordered_set<Flight, FlightHash, FlightEqual> getFlightsSet() const;

    ///Getter function of airportGraph_
    /// \return airportGraph_;
    Graph<Airport> getAirportGraph() const;
    set<string> getCitiesInCountryWithAirport(const string& country) const;
    vector<Vertex<Airport>*> getAirportsPerCity(const string& city) const;
    vector<Vertex<Airport>*> getAirportsPerCountry(const string& country) const;
    int getNumberOfFlightsPerAirline(const string& airline) const;
    int getAirportsNumber() const;
    int getAirlinesNumber() const;

};

#endif //PROJECT_II_SCRIPT_H

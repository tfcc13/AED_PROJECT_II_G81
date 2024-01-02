
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <benchmark/benchmark.h>
#include <iostream>
#include "Script.h"
#include "Airport.h"
#include "AirportManager.h"

using testing::Eq;



//=============================================================================
// Airport Total Flights
//=============================================================================

TEST(test_1, getAirportFlightsNumber) {

    cout << endl << "Testing 'Getting Airport Flights Number'" << endl;

    Script new_script = Script("script_test");

    string airportsCSV = "../../dataset/airports.csv";


    string flightsCSV = "../../dataset/flights.csv";


    new_script.loadAirports(airportsCSV);


    new_script.loadFlights(flightsCSV);

    AirportManager airportManager(new_script);

    int BCNDepartures = airportManager.getAirportFlightsNumber("BCN","departures");
    int OPODepartures =  airportManager.getAirportFlightsNumber("OPO","departures");
    int NVIDepartures = airportManager.getAirportFlightsNumber("NVI","departures");

    int BCNArrivals = airportManager.getAirportFlightsNumber("BCN","Arrivals");
    int OPOArrivals =  airportManager.getAirportFlightsNumber("OPO","Arrivals");
    int NVIArrivals = airportManager.getAirportFlightsNumber("NVI","Arrivals");

    int BCN = BCNDepartures+BCNArrivals;
    int OPO = OPODepartures+OPOArrivals;
    int NVI = NVIArrivals+NVIDepartures;

    EXPECT_EQ(774,BCN);
    EXPECT_EQ(202,OPO);
    EXPECT_EQ(12,NVI);

}

//=============================================================================
// Top K Airports
//=============================================================================

TEST(test_2, TopKAirports) {

    cout << endl << "Testing 'Identifing top K Airports'" << endl;

    Script new_script = Script("script_test");

    string airportsCSV = "../../dataset/airports.csv";

    string airlinesCSV = "../../dataset/airlines.csv";

    string flightsCSV = "../../dataset/flights.csv";


    new_script.loadAirports(airportsCSV);

    new_script.loadAirlines(airlinesCSV);

    new_script.loadFlights(flightsCSV);

    AirportManager airportManager(new_script);

    vector<pair<Airport,int>> topKAirport;

    topKAirport = airportManager.getTopKAiportTrafficCap(5);

    ASSERT_EQ(5, topKAirport.size());


}

TEST(test_3, Check_acyclic) {

    cout << endl << "Checking if the airport graph is acyclic" << endl;

    Script new_script = Script("script_test");

    string airportsCSV = "../../dataset/airports.csv";

    string airlinesCSV = "../../dataset/airlines.csv";

    string flightsCSV = "../../dataset/flights.csv";


    new_script.loadAirports(airportsCSV);

    new_script.loadAirlines(airlinesCSV);

    new_script.loadFlights(flightsCSV);

    bool checkDAG = new_script.getAirportGraph().isDAG();

    EXPECT_EQ(false, checkDAG);



}

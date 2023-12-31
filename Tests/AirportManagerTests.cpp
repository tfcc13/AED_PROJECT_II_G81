
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

    new_script.loadAirlines(airlinesCSV);

    new_script.loadFlights(flightsCSV);

    AirportManager airportManager(new_script);

    int BCN = airportManager.getAirportFlightsNumber("BCN");
    int OPO =  airportManager.getAirportFlightsNumber("OPO");
    int NVI = airportManager.getAirportFlightsNumber("NVI");

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
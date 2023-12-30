
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
// Top K Airports
//=============================================================================

TEST(test_1, TopKAirports) {

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
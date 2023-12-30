//
// Created by tiago on 11-12-2023.
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <benchmark/benchmark.h>

#include "Script.h"
#include "Airport.h"

using testing::Eq;


//=============================================================================
// Airports Loading
//=============================================================================

TEST(test_1, loadAirports) {

    cout << endl << "Testing 'loadAirports'" << endl;

    Script new_script = Script("script_test");

    string airportsCSV  = "../../dataset/airports.csv";

    new_script.loadAirports(airportsCSV);

    //auto airports = new_script.getAirportsMap();

    //int airportsSize = airports.size();

   // EXPECT_EQ(3019, airportsSize);

}


//=============================================================================
// Airlines Loading
//=============================================================================

TEST(test_2, loadAirlines) {

    cout << endl << "Testing 'loadAirlines'" << endl;

    Script new_script = Script("script_test");

    string airlinesCSV  = "../../dataset/airlines.csv";

    new_script.loadAirlines(airlinesCSV);


    int airlinesSize = new_script.getAirlinesNumber();

    EXPECT_EQ(444, airlinesSize);

}


//=============================================================================
// Flights Loading
//=============================================================================

TEST(test_3, loadFlights) {

    cout << endl << "Testing 'loadFlights'" << endl;

    Script new_script = Script("script_test");

    string flightsCSV  = "../../dataset/flights.csv";

    new_script.loadFlights(flightsCSV);

    auto flights = new_script.getFlightsSet();

    int flightsSize = flights.size();

    EXPECT_EQ(63832, flightsSize);

}


//=============================================================================
// Testing Airport Network
//=============================================================================

TEST(test_4, AirportNetwork) {

    cout << endl << "Testing 'createAirportNetwork'" << endl;

    Script new_script = Script("script_test");

    string airportsCSV  = "../../dataset/airports.csv";

    string airlinesCSV  = "../../dataset/airlines.csv";

    string flightsCSV  = "../../dataset/flights.csv";



    new_script.loadAirports(airportsCSV);

    new_script.loadAirlines(airlinesCSV);

    new_script.loadFlights(flightsCSV);


    vector<string>   airport_codes =  {"UKA", "CIY", "NVI", "ACX", "BCN"};

    int i = 0;
    int indegree = 0;
    int outdegree = 0;
    auto currAirport = new_script.getAirportGraph().findVertex(Airport(airport_codes[i]));


    outdegree = currAirport->getAdj().size();
    indegree = currAirport->getIndegree();

    EXPECT_EQ(1,outdegree);
    EXPECT_EQ(1,indegree);


    i++;

    currAirport = new_script.getAirportGraph().findVertex(Airport(airport_codes[i]));


    outdegree = currAirport->getAdj().size();
    indegree = currAirport->getIndegree();

    EXPECT_EQ(8,outdegree);
    EXPECT_EQ(8,indegree);


    i++;

    currAirport = new_script.getAirportGraph().findVertex(Airport(airport_codes[i]));


    outdegree = currAirport->getAdj().size();
    indegree = currAirport->getIndegree();
    int all_flights = outdegree+indegree;

    EXPECT_EQ(6,outdegree);
    EXPECT_EQ(6,indegree);
    EXPECT_EQ(12,all_flights);





    i++;

    currAirport = new_script.getAirportGraph().findVertex(Airport(airport_codes[i]));


    outdegree = currAirport->getAdj().size();
    indegree = currAirport->getIndegree();
    all_flights = outdegree+indegree;


    EXPECT_EQ(3,outdegree);
    EXPECT_EQ(3,indegree);
    EXPECT_EQ(6,all_flights);

    i++;

    currAirport = new_script.getAirportGraph().findVertex(Airport(airport_codes[i]));


    outdegree = currAirport->getAdj().size();
    indegree = currAirport->getIndegree();
    all_flights = outdegree+indegree;
    EXPECT_EQ(387,outdegree);
    EXPECT_EQ(387,indegree);
    EXPECT_EQ(774,all_flights);


}






//=============================================================================
// Google Benchmark
//=============================================================================


//=============================================================================
// Airports Loading
//=============================================================================

static void BM_loadAirports(benchmark::State& state) {


    for (auto _ : state) {
        state.PauseTiming();
        Script new_script = Script("script_test");
        std::string airportsCSV = "../../dataset/airports.csv";

        state.ResumeTiming();

        // Starts timing
        new_script.loadAirports(airportsCSV);
    }
    state.SetComplexityN(state.range(0));
}



//=============================================================================
// Airlines Loading
//=============================================================================

static void BM_loadAirlines(benchmark::State& state) {


    for (auto _ : state) {
        state.PauseTiming();
        Script new_script = Script("script_test");
        std::string airlinesCSV = "../../dataset/airlines.csv";

        state.ResumeTiming();

        // Starts timing
        new_script.loadAirlines(airlinesCSV);
    }
    state.SetComplexityN(state.range(0));
}



//=============================================================================
// Flights Loading
//=============================================================================

static void BM_loadFlights(benchmark::State& state) {


    for (auto _ : state) {
        state.PauseTiming();
        Script new_script = Script("script_test");
        std::string flightsCSV = "../../dataset/flights.csv";

        state.ResumeTiming();

        // Starts timing
        new_script.loadFlights(flightsCSV);
    }
    state.SetComplexityN(state.range(0));
}

//=============================================================================
// Register the functions as a benchmark
//=============================================================================

/*
BENCHMARK(BM_loadAirports)
        ->Unit(benchmark::kNanosecond)
        ->RangeMultiplier(2)->Range(1<<10, 1<<18)
        ->Complexity();
*/


/*
BENCHMARK(BM_loadAirlines)
        ->Unit(benchmark::kNanosecond)
        ->RangeMultiplier(2)->Range(1<<10, 1<<18)
        ->Complexity();
*/

/*
BENCHMARK(BM_loadFlights)
        ->Unit(benchmark::kNanosecond)
        ->RangeMultiplier(2)->Range(1<<10, 1<<18)
        ->Complexity();
*/
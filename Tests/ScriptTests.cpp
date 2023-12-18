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

    auto airports = new_script.getAirportsSet();

    int airportsSize = airports.size();

    EXPECT_EQ(3019, airportsSize);

}


//=============================================================================
// Airlines Loading
//=============================================================================

TEST(test_2, loadAirlines) {

    cout << endl << "Testing 'loadAirlines'" << endl;

    Script new_script = Script("script_test");

    string airlinesCSV  = "../../dataset/airlines.csv";

    new_script.loadAirlines(airlinesCSV);

    auto airlines = new_script.getAirlinesSet();

    int airlinesSize = airlines.size();

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
// Creating Airport Network
//=============================================================================

TEST(test_4, createAirportNetwork) {

    cout << endl << "Testing 'createAirportNetwork'" << endl;

    Script new_script = Script("script_test");

    string airportsCSV  = "../../dataset/airports.csv";

    string airlinesCSV  = "../../dataset/airlines.csv";

    string flightsCSV  = "../../dataset/flights.csv";



    new_script.loadAirports(airportsCSV);

    new_script.loadAirlines(airlinesCSV);

    new_script.loadFlights(flightsCSV);

    new_script.createAirportNetwork();

    string ukaTmpAirport = "UKA";

    auto ukaAirport = new_script.getAirportsSet().find(Airport(ukaTmpAirport));

    auto ukaVert = new_script.getAirportGraph().findVertex(*ukaAirport);

    int outdegree = ukaVert->getAdj().size();
    int indegree = ukaVert->getIndegree();

    EXPECT_EQ(1,outdegree);
    EXPECT_EQ(1,indegree);






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
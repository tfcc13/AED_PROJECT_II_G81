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

    string airportsCSV  = "/home/tiago/Desktop/FEUP/2Ano/1Semestre/AED/PROJECT_II/dataset/airports.csv";

    new_script.loadAirports(airportsCSV);

    auto airports = new_script.getAirportsSet();

    int airportsSize = airports.size();

    EXPECT_EQ(3019, airportsSize);

}


//

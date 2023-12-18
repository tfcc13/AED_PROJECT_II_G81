//
// Created by tiago on 11-12-2023.
//

#include "Script.h"

int main() {

    string airportsCSV  = "../../dataset/airports.csv";

    string airlinesCSV  = "../../dataset/airlines.csv";

    string flightsCSV  = "../../dataset/flights.csv";

    Script new_script = Script("Dataset");
    new_script.loadDataset()


    return 0;
}
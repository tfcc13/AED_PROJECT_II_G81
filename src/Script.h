//
// Created by tiago on 11-12-2023.
//

#ifndef PROJECT_II_SCRIPT_H
#define PROJECT_II_SCRIPT_H

#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Script {
private:
    string script_;
    set<Airport> all_airports_;
    set<Airline> all_airlines_;

public:


    /// Script constructor
    /// \param script name of the generated script class
    Script(const string& script);


    /// Loads the data from provided  csv files
    ///
    void loadDataset(const string& airports, const string& airlines);

    ///Populates all_airports_
    void loadAirports(const string& airports);


    ///Populates all_airlines_
    void loadAirlines(const string& airlines);


    ///Getter function of all_airports_
    /// \return all_airports_
    set<Airport> getAirportsSet() const;



};


#endif //PROJECT_II_SCRIPT_H

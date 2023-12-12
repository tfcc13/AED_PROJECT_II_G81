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
    ///**Time Complexity:** O(1)
    /// \param airports file with the airports data
    void loadAirports(const string& airports);


    ///Populates all_airlines_
    ///**Time Complexity:** O(1)
    /// \param airlines file with the airlines data
    void loadAirlines(const string& airlines);


    ///Getter function of all_airports_
    /// \return all_airports_
    set<Airport> getAirportsSet() const;

    ///Getter function of all_airlines_
    /// \return all_airports_
    set<Airline> getAirlinesSet() const;



};


#endif //PROJECT_II_SCRIPT_H

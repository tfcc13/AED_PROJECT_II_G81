//
// Created by tiago on 11-12-2023.
//

#ifndef PROJECT_II_AIRLINE_H
#define PROJECT_II_AIRLINE_H
#include <string>

using namespace std;
/// Class that represents an Airline Company

class Airline {

private:
    string airline_code_;
    string airline_name_;
    string callsign_;
    string country_;

public:

    ///Airline Constructor
    ///
    /// \param airline_code Airline unique code
    /// \param airline_name Airline name
    /// \param callsign Airline callsign
    /// \param country Airline headquarters country

    Airline(const string & airline_code, const string & airline_name, const string & callsign, const string & country );


    /// Getter function of airline_code_
    /// \return airline_code_
    const string& getAirlineCode() const;

    /// Getter function of airline_name_
    /// \return airline_name_
    const string& getAirlineName() const;

    /// Getter function of callsign_
    /// \return callsign_
    const string& getAirlineCallsign() const;


    /// Getter function of country_
    /// \return country_
    const string& getAirlineCountry() const;

    ///Operator < overload
    /// \param other Airline used for comparation
    /// return *true* if the current Airline code is lower alphabetically
    bool operator<(const Airline& other) const;




};


#endif //PROJECT_II_AIRLINE_H

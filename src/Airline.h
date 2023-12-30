#ifndef PROJECT_II_AIRLINE_H
#define PROJECT_II_AIRLINE_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/// Class that represents an Airline Company
class Airline {

private:
    string airline_code_;
    string airline_name_;
    string callsign_;
    string country_;
    int number_of_flights_;

public:

    ///Airline Constructor
    ///
    /// \param airline_code Airline unique code
    /// \param airline_name Airline name
    /// \param callsign Airline callsign
    /// \param country Airline headquarters country
    /// \param number_of_flights Total number of flights conducted by the airline in question

    Airline();

    Airline(const string & airline_code, const string & airline_name, const string& callsign, const string& country, int number_of_flights);

    size_t operator()(const Airline& airline) const;

    bool operator==(const Airline& other) const;

    void PrintAirlineName() const;

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

    void IncreaseTheNumberOfFlights();

};

#endif //PROJECT_II_AIRLINE_H

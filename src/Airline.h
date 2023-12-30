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
    /// Airline Default Constructor
    Airline();

    /// Airline Constructor
    ///
    /// \param airline_code Airline unique code
    /// \param airline_name Airline name
    /// \param callsign Airline callsign
    /// \param country Airline headquarters country
    /// \param number_of_flights Total number of flights conducted by the airline in question
    Airline(const string& airline_code, const string& airline_name, const string& callsign, const string& country, int number_of_flights);

    bool operator==(const Airline& other) const;

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

    /// Getter function of number_of_flights_
    /// \return number_of_flights_
    const int& getAirlineNumberOfFlights() const;

    /// Increase the airline's flight count by one. This function is utilized during the parsing of airlines.csv to ultimately calculate the total number of flights conducted by each airline
    void IncreaseTheNumberOfFlights();

    /// Print the airline's code, name, callsign, Country and the total number of performed flights
    void PrintAirlineInfo() const;

};

#endif //PROJECT_II_AIRLINE_H

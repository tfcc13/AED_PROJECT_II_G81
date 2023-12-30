#include "Airline.h"

Airline::Airline(){
    airline_code_ = "";
    airline_name_ = "";
    callsign_ = "";
    country_ = "";
    number_of_flights_ = 0;
}

Airline::Airline(const std::string &airline_code, const std::string &airline_name, const std::string &callsign, const std::string &country, int number_of_flights){
    airline_code_ = airline_code;
    airline_name_ = airline_name;
    callsign_ = callsign;
    country_ = country;
    number_of_flights_ = number_of_flights;
}

size_t Airline::operator()(const Airline& airline) const {
    return hash<string>{}(airline.airline_code_);
}

bool Airline::operator==(const Airline& other) const {
    return airline_code_ == other.airline_code_;
}

const string &Airline::getAirlineCode() const {
    return airline_code_;
}

const string &Airline::getAirlineName() const {
    return airline_name_;
}

const string &Airline::getAirlineCallsign() const {
    return callsign_;
}

const string &Airline::getAirlineCountry() const {
    return country_;
}

void Airline::PrintAirlineName() const {
    cout << left << setw(4) << airline_code_ << "|" << setw(10) << airline_name_ << "|" << setw(15) << callsign_ << "|" << setw(15) << country_ << endl << "|" << number_of_flights_;
}

void Airline::IncreaseTheNumberOfFlights() {
    number_of_flights_++;
}



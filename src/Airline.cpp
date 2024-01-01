#include "Airline.h"

Airline::Airline(){
    airline_code_ = "";
    airline_name_ = "";
    callsign_ = "";
    country_ = "";
    number_of_flights_ = 0;
}

Airline::Airline(const string& airline_code, const string& airline_name, const string& callsign, const string& country, int number_of_flights){
    airline_code_ = airline_code;
    airline_name_ = airline_name;
    callsign_ = callsign;
    country_ = country;
    number_of_flights_ = number_of_flights;
}

bool Airline::operator==(const Airline& other) const {
    return airline_code_ == other.airline_code_;
}

const string& Airline::getAirlineCode() const {
    return airline_code_;
}

const string& Airline::getAirlineName() const {
    return airline_name_;
}

const string& Airline::getAirlineCallsign() const {
    return callsign_;
}

const string& Airline::getAirlineCountry() const {
    return country_;
}

const int& Airline::getAirlineNumberOfFlights() const{
    return number_of_flights_;
}

void Airline::IncreaseTheNumberOfFlights() {
    number_of_flights_++;
}

void Airline::PrintAirlineInfo() const {
    cout << left << setw(4) << airline_code_ << "|" << setw(41) << airline_name_ << "|" << setw(26) << callsign_ << "|" << setw(37) << country_ << setw(17) << "|" << number_of_flights_ << endl;
}


//
// Created by tiago on 11-12-2023.
//

#include "Airline.h"

Airline::Airline(const string& airline_code, const string& airline_name, const string& callsign, const string& country) {

    airline_code_ = airline_code;
    airline_name_ = airline_name;
    callsign_ = callsign;
    country_ = country;

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

bool Airline::operator<(const Airline &other) const {
    return this->airline_code_ < other.airline_code_;
}

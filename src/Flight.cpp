//
// Created by tiago on 12-12-2023.
//

#include "Flight.h"



Flight::Flight(const string &src_airport, const string &dest_airport, const string &airline) {

    source_airport_ = src_airport;
    dest_airport_ = dest_airport;
    airline_ = airline;

}

size_t Flight::operator()(const Flight& flight) const {
    size_t hash = 0;
    hash_combine(hash, flight.source_airport_);
    hash_combine(hash, flight.dest_airport_);
    hash_combine(hash, flight.airline_);

}

const string &Flight::getSourceAirport() const {
    return source_airport_;
}

const string &Flight::getDestinationAirport() const {
    return dest_airport_;
}

const string &Flight::getAirline() const {
    return airline_;
}

bool Flight::operator==(const Flight &other) const {
    return source_airport_ == other.source_airport_ &&
            dest_airport_ == other.dest_airport_ &&
                    airline_ == other.airline_  ;
}

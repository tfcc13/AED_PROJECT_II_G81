//
// Created by tiago on 11-12-2023.
//

#include "Airport.h"

Airport::Airport(const string &airport_code, const string &airport_name, const string &airport_city,
                 const string &airport_country, const position &airport_position) {

}

Airport::Airport(const string &airport_code, const string &airport_name, const string &airport_city,
                 const string &airport_country, double &latitude, double &longitude) {

}


const string &Airport::getAirportCode() const {
    return airport_code_;
}

const string &Airport::getAirportName() const {
    return airport_name_;
}

const string &Airport::getAirportCity() const {
    return airport_city_;
}

const string &Airport::getAirportCountry() const {
    return airport_country_;
}

const position& Airport::getAirportPosition() const {
    return airport_position_;
}

void Airport::printAirportPosition() const {
    cout << "Latitude: " << airport_position_.lattitude << endl;
    cout << "Longitude: " << airport_position_.longitude << endl;
    cout << endl;

}

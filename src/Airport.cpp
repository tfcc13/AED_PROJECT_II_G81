#include "Airport.h"


Airport::Airport() {

}

Airport::Airport(const string &airport_code, const string &airport_name, const string &airport_city,
                 const string &airport_country, const position &airport_position) {

    airport_code_ = airport_code;
    airport_name_ = airport_name;
    airport_city_ = airport_city;
    airport_country_ = airport_country;
    airport_position_ = airport_position;

}

Airport::Airport(const string &airport_code, const string &airport_name, const string &airport_city,
                 const string &airport_country, double latitude, double longitude) {

    airport_code_ = airport_code;
    airport_name_ = airport_name;
    airport_city_ = airport_city;
    airport_country_ = airport_country;
    airport_position_.latitude = latitude;
    airport_position_.longitude = longitude;

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
    cout << "Latitude: " << airport_position_.latitude << endl;
    cout << "Longitude: " << airport_position_.longitude << endl;
    cout << endl;

}

bool Airport::operator<(const Airport &other) const {
    return this->airport_code_<other.airport_code_;
}

bool Airport::operator==(const Airport &other) const {
   /* return (this->airport_position_ == other.airport_position_ &&
    this->airport_code_ == other.airport_code_ &&
    this->airport_country_ == other.airport_country_ &&
    this->airport_city_==other.airport_city_ &&
    this->airport_name_==other.airport_name_);
    */

   return (this->airport_code_ == other.airport_code_);
}


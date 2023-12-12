//
// Created by tiago on 11-12-2023.
//

#include <cstring>
#include "Script.h"

Script::Script(const string &script) {

    script_ = script;
}

void Script::loadDataset(const string &airports, const string &airlines) {
    loadAirports(airports);
    loadAirlines(airlines);
}

void Script::loadAirports(const string &airports) {

    ///Tries to open input file
    std::ifstream dataAirports(airports);

    /// If the system fails to open the file, user gets a warning, and the function terminates
    if(dataAirports.fail()) {
        cerr << "Error Warning: Unable to open the file " << airports << endl;
        cerr << "Error details: " << strerror(errno) << endl;
        cout << endl;
        return;
    }

    ///Opening input file is successful

    string header;
    getline(dataAirports, header);
    string line;
    string airport_code;
    string airport_name;
    string airport_city;
    string airport_country;
    double latitude;
    double longitude;
    string tempLat;
    string tempLong;
    position airportPos;

    char sep = ',';

    while( getline(dataAirports,line)) {

        istringstream iss(line);

        getline(iss,airport_code, sep);
        getline(iss,airport_name, sep);
        getline(iss,airport_city, sep);
        getline(iss,airport_country, sep);
        getline(iss,tempLat, sep);
        getline(iss,tempLong, '\r');

        latitude = stod(tempLat);
        longitude = stod(tempLong);

        airportPos = {latitude, longitude};

        Airport tempAirport = Airport(airport_code, airport_name, airport_city, airport_country, airportPos);

        all_airports_.insert(tempAirport);
    }


 dataAirports.close();
}

void Script::loadAirlines(const string &airlines) {

    ///Tries to open input file
    std::ifstream dataAirlines(airlines);

    /// If the system fails to open the file, user gets a warning, and the function terminates
    if(dataAirlines.fail()) {
        cerr << "Error Warning: Unable to open the file " << airlines << endl;
        cerr << "Error details: " << strerror(errno) << endl;
        cout << endl;
        return;
    }

    ///Opening input file is successful

    string header;
    getline(dataAirlines, header);
    string line;
    string airline_code;
    string airline_name;
    string callsign;
    string country;

    char sep = ',';

    while( getline(dataAirlines,line)) {

        istringstream iss(line);

        getline(iss,airline_code, sep);
        getline(iss,airline_name, sep);
        getline(iss,callsign, sep);
        getline(iss,country, '\r');

        Airline tempAirline = Airline(airline_code, airline_name, callsign, country);

        all_airlines_.insert(tempAirline);
    }


    dataAirlines.close();

}

set<Airport> Script::getAirportsSet() const {
    return all_airports_;
}

set<Airline> Script::getAirlinesSet() const {
    return all_airlines_;
}

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

    ///Ignores the header line
    string header;
    getline(dataAirports, header);

    ///creates the temporary line string
    string line;


    ///creates the temporary strings to extract the airport code, name, city, country, latitude and longitude
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

        cout << tempLat;

        istringstream(tempLat) >> latitude;
        istringstream(tempLong) >> longitude;


        airportPos = {latitude, longitude};

        ///it's created an Airport object whith the extracted info
        Airport tempAirport = Airport(airport_code, airport_name, airport_city, airport_country, airportPos);

        ///The Airport object is inserted in all_airports_ set
        all_airports_.insert(tempAirport);
    }

/// File is closed after parsing all the data
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
    ///creates the temporary strings to extract the airlines code, name, callsign and country

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

        ///it's created an Airline object whith the extracted info
        Airline tempAirline = Airline(airline_code, airline_name, callsign, country);

        ///The Airline object is inserted in all_airlines_ set
        all_airlines_.insert(tempAirline);
    }


    dataAirlines.close();

}

void Script::loadFlights(const string &flights) {
    ///Tries to open input file
    std::ifstream dataFlights(flights);

    /// If the system fails to open the file, user gets a warning, and the function terminates
    if(dataFlights.fail()) {
        cerr << "Error Warning: Unable to open the file " << flights << endl;
        cerr << "Error details: " << strerror(errno) << endl;
        cout << endl;
        return;
    }

    ///Opening input file is successful

    string header;
    getline(dataFlights, header);

    string line;
    ///creates the temporary strings to extract the Flight source Airport, destination Airport, and Airline

    string source_airport;
    string dest_airport;
    string airline;


    char sep = ',';

    while( getline(dataFlights,line)) {

        istringstream iss(line);

        getline(iss,source_airport, sep);
        getline(iss,dest_airport, sep);
        getline(iss,airline, '\r');

        ///it's created an Flight object whith the extracted info
        Flight tempFlight = Flight(source_airport,dest_airport,airline);

        ///The Flight object is inserted in all_flights_ set
        all_flights_.insert(tempFlight);
    }


    dataFlights.close();

}


set<Airport> Script::getAirportsSet() const {
    return all_airports_;
}

set<Airline> Script::getAirlinesSet() const {
    return all_airlines_;
}

unordered_set<Flight, FlightHash,FlightEqual> Script::getFlightsSet() const {
    return all_flights_;
}


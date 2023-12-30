#include <cstring>
#include "Script.h"

Script::Script(const string &script) {

    script_ = script;
    loadDataset(airportsCSV,airlinesCSV,flightsCSV);

}

void Script::loadDataset(const string &airports, const string &airlines, const string& flights) {

    loadAirports(airports);
    loadAirlines(airlines);
    loadFlights(flights);

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

        istringstream(tempLat) >> latitude;
        istringstream(tempLong) >> longitude;

        airportPos = {latitude, longitude};

        ///it's created an Airport object with the extracted info
        Airport tempAirport = Airport(airport_code, airport_name, airport_city, airport_country, airportPos);

        ///The Airport object is inserted in all_airports_ set
        Vertex<Airport>* newVertex = airportGraph_.addVertex(tempAirport);

        all_airports_.insert(make_pair(airport_code, newVertex));

        auto it_country = cities_per_country_.find(airport_country);
        if(it_country == cities_per_country_.end()){
            cities_per_country_[airport_country] = {airport_city};
        } else{
            cities_per_country_[airport_country].insert(airport_city);
        }

        auto it_city = airports_per_city_and_country_.find(airport_city);

        if (it_city == airports_per_city_and_country_.end()) {
            airports_per_city_and_country_[airport_city] = {{airport_country, {newVertex}}};
        } else {
            auto& country_map = it_city->second;
            auto it_city_s_country = country_map.find(airport_country);

            if (it_city_s_country == country_map.end()) {
                country_map[airport_country] = {newVertex};
            } else {
                country_map[airport_country].push_back(newVertex);
            }
        }


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

        ///it's created an Airline object with the extracted info
        Airline tempAirline = Airline(airline_code, airline_name, callsign, country, 0);

        ///The Airline object is inserted in all_airlines_ set
        all_airlines_[airline_code] = tempAirline;
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

        all_airlines_[airline].IncreaseTheNumberOfFlights();

        ///it's created an Flight object with the extracted info
        Flight tempFlight = Flight(source_airport,dest_airport,airline);


       /* std::unordered_map<std::string, Airport>::iterator airportSrcMapValue = all_airports_.find(source_airport);
        std::unordered_map<std::string, Airport>::iterator airportDestMapValue = all_airports_.find(dest_airport);


        if(airportSrcMapValue != getAirportsMap().end()  && airportDestMapValue != getAirportsMap().end()) {

            auto tmpSrcVert = airportGraph_.findVertex(airportSrcMapValue->second);
            auto tmpDestVert = airportGraph_.findVertex(airportDestMapValue->second);

            if (tmpSrcVert != nullptr && tmpDestVert != nullptr) {
                airportGraph_.addEdge(tmpSrcVert->getInfo(), tmpDestVert->getInfo(), 0, airline);
                tmpDestVert->setIndegree(tmpDestVert->getIndegree() + 1);
            }
        }
        */

       Airport tmpSrcAirport = Airport(source_airport);
       Airport tmpDestAirport = Airport(dest_airport);

       auto tmpSrcVert = airportGraph_.findVertex(tmpSrcAirport);
       auto tmpDestVert = airportGraph_.findVertex(tmpDestAirport);

        if (tmpSrcVert != nullptr && tmpDestVert != nullptr) {
            airportGraph_.addEdge(tmpSrcVert->getInfo(), tmpDestVert->getInfo(), 0, airline);
            tmpDestVert->setIndegree(tmpDestVert->getIndegree() + 1);
        }

        ///The Flight object is inserted in all_flights_ set
        all_flights_.insert(tempFlight);


    }

    dataFlights.close();

}


unordered_set<Flight, FlightHash,FlightEqual> Script::getFlightsSet() const {
    return all_flights_;
}

Graph<Airport> Script::getAirportGraph() const {
    return airportGraph_;
}

set<string> Script::getCitiesInCountryWithAirport(const string& country) const{
    auto it = cities_per_country_.find(country);
    if(it != cities_per_country_.end()){
        return it->second;
    } else{
        {};
    }
}

int Script::getAirportsNumber() const {
    return int(all_airports_.size());
}

int Script::getAirlinesNumber() const {
    return int(all_airlines_.size());
}

/*
vector<Vertex<Airport>*> Script::getAirportsPerCity(const string& city) const{
    auto it = airports_per_city_.find(city);
    if(it != airports_per_city_.end()){
        return it->second;
    } else{
        {};
    }
}

vector<Vertex<Airport>*> Script::getAirportsPerCountry(const string& country) const {
    set<string> cities_set = getCitiesInCountryWithAirport(country);

    vector<Vertex<Airport>*> airports_in_country;

    for (const auto& city : cities_set) {
        auto it = airports_per_city_.find(city);
        if (it != airports_per_city_.end()) {
            airports_in_country.insert(airports_in_country.end(), it->second.begin(), it->second.end());
        }
    }

    return airports_in_country;
}

int Script::getNumberOfFlightsPerAirline(const string& airline) const{
    auto it = flights_per_airline_.find(airline);
    if(it != flights_per_airline_.end()){
        return it->second;
    } else{
        return 0;
    }
}
*/


#include <cstring>
#include "Script.h"

Script::Script(const string &script) {

    script_ = script;
    //loadDataset(airportsCSV,airlinesCSV,flightsCSV);

}

void Script::loadDataset(const string &airports, const string &airlines, const string& flights) {

    loadAirports(airports);
    loadAirlines(airlines);
    loadFlights(flights);

}

void Script::loadAirports(const string &airports) {

    /// Tries to open input file
    std::ifstream dataAirports(airports);

    /// If the system fails to open the file, user gets a warning, and the function terminates
    if(dataAirports.fail()) {
        cerr << "Error Warning: Unable to open the file " << airports << endl;
        cerr << "Error details: " << strerror(errno) << endl;
        cout << endl;
        return;
    }

    /// Opening input file is successful

    /// Ignores the header line
    string header;
    getline(dataAirports, header);

    /// Creates the temporary line string
    string line;

    /// Creates the temporary strings to extract the airport code, name, city, country, latitude and longitude
    string airport_code;
    string airport_name;
    string airport_city;
    string airport_country;
    double latitude;
    double longitude;
    string tempLat;
    string tempLong;
    position airportPos{};

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

        /// It's created an Airport object with the extracted info
        Airport tempAirport = Airport(airport_code, airport_name, airport_city, airport_country, airportPos);

        /// The tempAirport object is added as a vertex to the airportGraph_
        /// The addVertex function was modified to return a self reference for inclusion in all_airports_
        /// The reference to the Airport vertex object is inserted into all_airports_, mapping each airport code to the corresponding vertex in the airportGraph_
        Vertex<Airport>* newVertex = airportGraph_.addVertex(tempAirport);
        all_airports_.insert(make_pair(airport_code, newVertex));

        /// Each city with an airport is mapped to a country in the cities_per_country_ structure
        auto it_country = cities_per_country_.find(airport_country);
        if(it_country == cities_per_country_.end()){
            cities_per_country_[airport_country] = {airport_city};
        } else{
            it_country->second.insert(airport_city);
        }

        /// The reference to the Airport vertex object is mapped to the corresponding Country and City in the airports_per_city_and_country_ structure
        /// This structure enables checking all Airport vertices in a particular city, considering that a city may have the same name in different Countries
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

        /// The Airline object is inserted into the all_airlines_ map, which will also track the total number of flights made
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

    while(getline(dataFlights,line)) {

        istringstream iss(line);

        getline(iss,source_airport, sep);
        getline(iss,dest_airport, sep);
        getline(iss,airline, '\r');

        /// The number of flights performed by the current's airline is increased
        all_airlines_[airline].IncreaseTheNumberOfFlights();

        /// It's created an Flight object with the extracted info
        Flight tempFlight = Flight(source_airport,dest_airport,airline);

        auto srcVert_pair = all_airports_.find(source_airport);
        auto destVert_pair = all_airports_.find(dest_airport);

        if(srcVert_pair != nullptr and destVert_pair != nullptr){
            auto srcVert = srcVert_pair->second;
            auto destVert = destVert_pair->second;
            airportGraph_.addEdge(srcVert->getInfo(), destVert->getInfo(), 0, airline);
            airportGraph_.addIncomingEdge(srcVert->getInfo(), destVert->getInfo(), 0, airline);
        }

        ///The Flight object is inserted in all_flights_ set
        all_flights_.insert(tempFlight);

    }

    airportGraph_.setIndegree();

    dataFlights.close();

}

unordered_set<Flight, FlightHash,FlightEqual> Script::getFlightsSet() const {
    return all_flights_;
}

Graph<Airport> Script::getAirportGraph() const {
    return airportGraph_;
}

const unordered_map<string, Vertex<Airport> *> Script::getAllAirports() const {
    return all_airports_;
}



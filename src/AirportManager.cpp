#include "AirportManager.h"

AirportManager::AirportManager(Script& script) : script_(script) {}

int AirportManager::getAirportFlightsNumber(const string &airport_name) {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));

    if(airportVert == NULL) return -1;

    return airportVert->getAdj().size();
}

int AirportManager::getAirportAirlinesNumber(const string &airport_name) {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));

    if(airportVert == NULL) return -1;

    set<string> airlinesSet = getAirlinesSet(airport_name);

    return airlinesSet.size();
}

const set<string> AirportManager::getCitiesSet(const string &airport_name) const {
    set<string> cities;

    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    if(airportVert == NULL) return cities;

    for (auto airlines : airportVert->getAdj()) {
        auto airportDest = airlines.getDest();
        cities.insert(airportDest->getInfo().getAirportCity());
    }

    return cities;
}

const set<string> AirportManager::getAirlinesSet(const string &airport_name) const {
    set<string> airlinesSet;

    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    if(airportVert == NULL) return airlinesSet;

    for (auto airlines : airportVert->getAdj()) {
        auto airline = airlines.getAirline();
        airlinesSet.insert(airline);
    }

    return airlinesSet;
}

int AirportManager::getDestinationCitiesNumber(const string& airport_name) {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    if(airportVert == NULL) return -1;

    set<string> cities;

    cities = getCitiesSet(airport_name);

    return cities.size();
}

const string &AirportManager::getAirportName(const string &airport_name) const {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    string notFound = "Not found";
    if(airportVert == NULL) return notFound;

    return airportVert->getInfo().getAirportName();
}

void AirportManager::getDestinationCitiesNames(const string &airport_name) const {

    auto cities = getCitiesSet(airport_name);

    cout << left << "City" << endl;

    for (auto city : cities) {
        cout << left << city << endl;
    }

}

void AirportManager::PrintAirlinesNames(const string &airport_name) const {

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "Callsign" << "|" << setw(15) << "Country" << "|" << setw(5) << "Number of flights" << endl;

    for(const auto& airline : script_.all_airlines_){
        airline.second.PrintAirlineName();
    }

}

const set<Airport> AirportManager::getAirportsSet(const string &airport_name) const {
    set<Airport> airportsSet;

    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    if(airportVert == NULL) return airportsSet;

    for (const auto& edge : airportVert->getAdj()) {
        auto dest = edge.getDest();
        Airport airport = dest->getInfo();
        airportsSet.insert(airport);
    }

    return airportsSet;

}

int AirportManager::getDestinationAirportsNumber(const string &airport_name) {
    auto airportVert = script_.all_airports_[airport_name];
    if(airportVert == NULL) return -1;

    auto airportSet = getAirportsSet(airport_name);

    return airportSet.size();

}

void AirportManager::getDestinationAirportsNames(const string &airport_name) {

    auto airportSet = getAirportsSet(airport_name);

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << endl;

    for(auto airport: airportSet) {
        cout << left << setw(4) << airport.getAirportCode() << "|" << setw(10) << airport.getAirportName() << "|" << setw(15) << airport.getAirportCity() << "|" << setw(15) << airport.getAirportCountry() << endl;
    }

}

void AirportManager::getAirportsFlightsData(const string &airport_name) const {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport_name));
    if(airportVert == NULL) {
        cout << "That airport doesn't exist in Airtuga database" << endl;
        cout << endl;
        return;
    }

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << "|" <<  setw(15) << "Airline" << endl;
    for (auto edge : airportVert->getAdj()) {
        auto destAirport = edge.getDest();
        auto airline  = edge.getAirline();
        string airportCode = destAirport->getInfo().getAirportCode();
        string airportName= destAirport->getInfo().getAirportName();
        string city = destAirport->getInfo().getAirportCity();
        string airportCountry = destAirport->getInfo().getAirportCountry();

        cout << left << setw(4) << airportCode << "|" << setw(10) << airportName << "|" << setw(15) << city << "|" << setw(15) << airportCountry << "|" <<  setw(15) << airline << endl;

    }

}

int AirportManager::getDestinationCountriesNumber(const string &airport) const {
    auto airportVert = script_.airportGraph_.findVertex(Airport(airport));
    if(airportVert == NULL) return -1;

    auto countries = getDestinationCountriesSet(airport);

    return countries.size();

}

const set<string> AirportManager::getDestinationCountriesSet(const string &airport) const {
    set<string> countriesSet;

    auto airportVert = script_.airportGraph_.findVertex(Airport(airport));
    if(airportVert == NULL) return countriesSet;

    for(auto edge: airportVert->getAdj()) {
        auto dest = edge.getDest()->getInfo();
        string country = dest.getAirportCountry();
        countriesSet.insert(country);
    }

    return countriesSet;

}

void AirportManager::getDestinationCountriesNames(const string &airport) const {


    auto airportVert = script_.airportGraph_.findVertex(Airport(airport));
    if(airportVert == NULL) {
        cout << "That airport doesn't exist in Airtuga database" << endl;
        cout << endl;
        return;
    }
    set<string> countriesSet = getDestinationCountriesSet(airport);

    cout << left << "Country" << endl;

    for(auto country: countriesSet) {
        cout << left << country << endl;
    }


}


//
// Created by tiago on 19-12-2023.
//

#include "AirportManager.h"

AirportManager::AirportManager(Script& script) : script_(script) {}

int AirportManager::getAirportFlightsNumber(const string &airport) {

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));

    if(airportVert == NULL) return -1;

    return airportVert->getAdj().size();


}

int AirportManager::getAirportAirlinesNumber(const string &airport) {
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));

    if(airportVert == NULL) return -1;

    set<string> airlinesSet = getAirlinesSet(airport);

    return airlinesSet.size();

}

const set<string> AirportManager::getCitiesSet(const string &airport) const {
    set<string> cities;

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return cities;

    for (auto airlines : airportVert->getAdj()) {
        auto airportDest = airlines.getDest();
        cities.insert(airportDest->getInfo().getAirportCity());
    }

    return cities;

}

const set<string> AirportManager::getAirlinesSet(const string &airport) const {
    set<string> airlinesSet;

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return airlinesSet;

    for (auto airlines : airportVert->getAdj()) {
        auto airline = airlines.getAirline();
        airlinesSet.insert(airline);
    }

    return airlinesSet;




}



int AirportManager::getDestinationCitiesNumber(const string& airport) {
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return -1;

    set<string> cities;

    cities = getCitiesSet(airport);

    return cities.size();

}

const string &AirportManager::getAirportName(const string &airport) const {
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    string notFound = "Not found";
    if(airportVert == NULL) return notFound;

    return airportVert->getInfo().getAirportName();

}

void AirportManager::getDestinationCitiesNames(const string &airport) const {

    auto cities = getCitiesSet(airport);

    cout << left << "City" << endl;

    for (auto city : cities) {
        cout << left << city << endl;
    }


}

void AirportManager::getAirlinesNames(const string &airport) const {

    auto airlines = getAirlinesSet(airport);

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "Callsign" << "|" << setw(15) << "Country" << endl;

    for(auto airline:airlines) {
        auto vert = script_.getAirlineGraph().findVertex(Airline(airline));
        cout << left << setw(4) << airline << "|" << setw(10) << vert->getInfo().getAirlineName() << "|" << setw(15) << vert->getInfo().getAirlineCallsign() << "|" << setw(15) << vert->getInfo().getAirlineCountry() << endl;
    }

}

const set<Airport> AirportManager::getAirportsSet(const string &airport) const {
    set<Airport> airportsSet;

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return airportsSet;

    for (auto edge : airportVert->getAdj()) {
        auto dest = edge.getDest();
        Airport airport = dest->getInfo();
        airportsSet.insert(airport);
    }

    return airportsSet;


}

int AirportManager::getDestinationAirportsNumber(const string &airport) {
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return -1;

    auto airportSet = getAirportsSet(airport);

    return airportSet.size();

}

void AirportManager::getDestinationAirportsNames(const string &airport) {

    auto airportSet = getAirportsSet(airport);

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << endl;

    for(auto airport: airportSet) {
        cout << left << setw(4) << airport.getAirportCode() << "|" << setw(10) << airport.getAirportName() << "|" << setw(15) << airport.getAirportCity() << "|" << setw(15) << airport.getAirportCountry() << endl;
    }

}


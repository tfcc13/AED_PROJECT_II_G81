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

void AirportManager::getAirportsFlightsData(const string &airport) const {
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
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
    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return -1;

    auto countries = getDestinationCountriesSet(airport);

    return countries.size();

}

const set<string> AirportManager::getDestinationCountriesSet(const string &airport) const {
    set<string> countriesSet;

    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
    if(airportVert == NULL) return countriesSet;

    for(auto edge: airportVert->getAdj()) {
        auto dest = edge.getDest()->getInfo();
        string country = dest.getAirportCountry();
        countriesSet.insert(country);
    }

    return countriesSet;

}

void AirportManager::getDestinationCountriesNames(const string &airport) const {


    auto airportVert = script_.airportGraph.findVertex(Airport(airport));
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

vector<pair<Airport,int>> AirportManager::getTopKAiportTrafficCap(int k) const {
    vector<pair<Airport,int>> topKAirports;
    for (auto v : script_.airportGraph.getVertexSet()) {
        int inFlights = v->getIndegree();
        int outFlights = v->getAdj().size();
        int flightsCount = inFlights+outFlights;
        topKAirports.push_back(make_pair(v->getInfo(),flightsCount));
    }

    sort(topKAirports.begin(),topKAirports.end(), [] (const auto& a, const auto& b){return a.second > b.second;});
    topKAirports = vector<pair<Airport,int>> (topKAirports.begin(), topKAirports.begin()+k);
    return topKAirports;
}

void AirportManager::printAllAirports() const {

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << "|" <<  setw(15) << "Airline" << endl;
    for (auto airport : script_.airportGraph.getVertexSet()) {
        string airportCode = airport->getInfo().getAirportCode();
        string airportName= airport->getInfo().getAirportName();
        string city = airport->getInfo().getAirportCity();
        string airportCountry = airport->getInfo().getAirportCountry();

        cout << left << setw(4) << airportCode << "|" << setw(10) << airportName << "|" << setw(15) << city << "|" << setw(15) << airportCountry << "|" <<  setw(15) << endl;

    }

}

set<Airport> AirportManager::airportArticulationPoints() {

    Graph<Airport> undGraph;

    for (auto v : script_.airportGraph.getVertexSet()) {
        undGraph.addVertex(v->getInfo());
    }

    for(auto v :  script_.airportGraph.getVertexSet()) {
        for(const auto& edge : v->getAdj()) {
            auto dest = edge.getDest();
            undGraph.addEdge(dest->getInfo(), v->getInfo(),0);
        }
    }


    set<Airport> res;
    stack<Airport> s;
    int  i = 0;


    for (auto& v :  undGraph.getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    for(auto & v: undGraph.getVertexSet()) {
        if(!v->isVisited()) {
            dfs_art(undGraph, v, s, res, i);
        }
    }

    return res;

}

void AirportManager::dfs_art(Graph<Airport>& g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i) {
    v->setVisited(true);
    v->setProcessing(true);

    v->setNum(i);
    v->setLow(i);

    i++;

    s.push(v->getInfo());
    int children =0;

    for(auto & edge : v->getAdj()) {
        auto dest = edge.getDest();

        if(!dest->isVisited()) {
            children++;
            dfs_art(g, dest,s,l,i);
            v->setLow(min(v->getLow(),dest->getLow()));
            if(dest->getLow()>= v->getNum() && s.size() > 1 ) {
                l.insert(v->getInfo());
            }

        }
        else if(dest->isProcessing()) {
            v->setLow(min(v->getLow(),dest->getNum()));
        }
    }

    if(v->getNum()==0 && children>1) {
        l.insert(v->getInfo());
    }

    s.pop();
    v->setProcessing(false);

}


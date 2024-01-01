#include "AirportManager.h"

AirportManager::AirportManager(Script& script) : script_(script) {}
// OK
int AirportManager::getAirportFlightsNumber(const string& airport_name, const string& departures_or_arrivals) {

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return -1;
    }

    vector<Edge<Airport>> edges;
    if(departures_or_arrivals == "departures"){
        edges = airport->second->getAdj();
    } else {
        edges = airport->second->getIncomingEdges();
    }

    return int(edges.size());
}
// OK
int AirportManager::getAirportAirlinesNumber(const string& airport_name, const string& departures_or_arrivals) {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return -1;
    }

    set<string> airlinesSet = getAirlinesSet(airport_name, departures_or_arrivals);

    return int(airlinesSet.size());
}
// OK
set<string> AirportManager::getCitiesSet(const string &airport_name, const string& departures_or_arrivals) const {
    set<string> cities;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return cities;
    }

    vector<Edge<Airport>> edges;
    if(departures_or_arrivals == "departures"){
        edges = airport->second->getAdj();
    } else {
        edges = airport->second->getIncomingEdges();
    }

    for (const auto& edge : edges) {
        auto airportDest = edge.getDest();
        cities.insert(airportDest->getInfo().getAirportCity());
    }

    return cities;
}

set<string> AirportManager::getAirlinesSet(const string& airport_name, const string& departures_or_arrivals) const {
    set<string> airlinesSet;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return airlinesSet;
    }
    auto teste = airport->second;
    cout << teste->getAdj().size() << " " << teste->getIncomingEdges().size();

    vector<Edge<Airport>> edges;
    if(departures_or_arrivals == "departures"){
        edges = airport->second->getAdj();
    } else {
        edges = airport->second->getIncomingEdges();
    }

    for (const auto& edge : edges) {
        auto airline = edge.getAirline();
        airlinesSet.insert(airline);
    }

    return airlinesSet;
}
// OK
int AirportManager::getDestinationCitiesNumber(const string& airport_name, const string& departures_or_arrivals) {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return -1;
    }

    set<string> cities;

    cities = getCitiesSet(airport_name, departures_or_arrivals);

    return int(cities.size());
}

const string &AirportManager::getAirportName(const string &airport_name) const {
    string notFound = "Not found";
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return notFound;
    }

    return airport->second->getInfo().getAirportName();
}
// OK
void AirportManager::getDestinationCitiesNames(const string &airport_name, const string& departures_or_arrivals) const {

    auto cities = getCitiesSet(airport_name, departures_or_arrivals);

    cout << left << "City" << endl << endl;

    for (const auto& city : cities) {
        cout << left << city << endl;
    }

}
// OK
void AirportManager::printAirlinesNames(const string &airport_name, const string& departures_or_arrivals) const {

    auto airlines = getAirlinesSet(airport_name, departures_or_arrivals);

    cout << left << setw(4) << "Code" << "|" << setw(41) << "Name" << "|" << setw(26) << "Callsign" << "|" << setw(37) << "Country" << "|" << setw(17) << "Number of flights" << endl << endl;

    for(const auto& airline : airlines){
        script_.all_airlines_.find(airline)->second.PrintAirlineInfo();
    }

}

set<Airport> AirportManager::getAirportsSet(const string &airport_name) const {
    set<Airport> airportsSet;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return airportsSet;
    }

    for (const auto& edge : airport->second->getAdj()) {
        airportsSet.insert(edge.getDest()->getInfo());
    }

    return airportsSet;

}

int AirportManager::getDestinationAirportsNumber(const string &airport_name) {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return -1;
    }

    auto airportSet = getAirportsSet(airport_name);

    return int(airportSet.size());

}

void AirportManager::getDestinationAirportsNames(const string &airport_name) const {

    auto airportSet = getAirportsSet(airport_name);

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << endl;

    for(const auto& airport: airportSet) {
        cout << left << setw(4) << airport.getAirportCode() << "|" << setw(10) << airport.getAirportName() << "|" << setw(15) << airport.getAirportCity() << "|" << setw(15) << airport.getAirportCountry() << endl;
    }

}
// OK
void AirportManager::getAirportsFlightsData(const string& airport_name, const string& departures_or_arrivals) const {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        cout << "That airport doesn't exist in Airtuga database" << endl;
        cout << endl;
        return;
    }

    cout << left << setw(4) << "Code" << "|" << setw(55) << "Name" << "|" << setw(30) << "City" << "|" << setw(32) << "Country" << "|" <<  setw(7) << "Airline" << endl << endl;

    vector<Edge<Airport>> edges;
    if(departures_or_arrivals == "departures"){
        edges = airport->second->getAdj();
    } else {
        edges = airport->second->getIncomingEdges();
    }

    for (const auto& edge : edges) {
        auto destAirport = edge.getDest();
        auto airline  = edge.getAirline();
        string airportCode = destAirport->getInfo().getAirportCode();
        string airportName= destAirport->getInfo().getAirportName();
        string city = destAirport->getInfo().getAirportCity();
        string airportCountry = destAirport->getInfo().getAirportCountry();

        cout << left << setw(4) << airportCode << "|" << setw(55) << airportName << "|" << setw(30) << city << "|" << setw(32) << airportCountry << "|" <<  setw(3) << airline << endl;

    }

}

int AirportManager::getDestinationCountriesNumber(const string &airport_name, const string& departures_or_arrivals) const {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return -1;
    }

    auto countries = getDestinationCountriesSet(airport_name, departures_or_arrivals);

    return int(countries.size());

}

set<string> AirportManager::getDestinationCountriesSet(const string &airport_name, const string& departures_or_arrivals) const {
    set<string> countriesSet;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return countriesSet;
    }

    vector<Edge<Airport>> edges;
    if(departures_or_arrivals == "departures"){
        edges = airport->second->getAdj();
    } else {
        edges = airport->second->getIncomingEdges();
    }

    for(const auto& edge: edges) {
        auto dest = edge.getDest()->getInfo();
        const string& country = dest.getAirportCountry();
        countriesSet.insert(country);
    }

    return countriesSet;

}

void AirportManager::getDestinationCountriesNames(const string &airport_name, const string& departures_or_arrivals) const {
    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        cout << "That airport doesn't exist in Airtuga database" << endl;
        cout << endl;
        return;
    }

    set<string> countriesSet = getDestinationCountriesSet(airport_name, departures_or_arrivals);

    cout << left << "Country" << endl;

    for(const auto& country: countriesSet) {
        cout << left << country << endl;
    }

}

int AirportManager::getFlightsPerCity(const string& city, const string& country) const{

    int counter = 0;

    auto airports = getAirportsPerCityAndCountry(city, country);

    if(airports.empty()){
        return -1;
    }

    for(const auto& airport : airports){
        counter += int(airport->getAdj().size()) + int(airport->getIncomingEdges().size());
    }

    return counter;

}

int AirportManager::getFlightsPerAirline(const string& airline) const{

    auto it = script_.all_airlines_.find(airline);

    if(it == script_.all_airlines_.end()){
        return -1;
    }

    return it->second.getAirlineNumberOfFlights();

}

vector<pair<Airport,int>> AirportManager::getTopKAiportTrafficCap(int k) const {
    vector<pair<Airport,int>> topKAirports;

    for(auto& vertex : script_.airportGraph_.getVertexSet()){
        topKAirports.emplace_back(vertex->getInfo(), vertex->getIndegree() + int(vertex->getAdj().size()));
    }

    sort(topKAirports.begin(),topKAirports.end(), [] (const auto& a, const auto& b){return a.second > b.second;});
    topKAirports = vector<pair<Airport,int>> (topKAirports.begin(), topKAirports.begin()+k);
    return topKAirports;
}

void AirportManager::printAllAirports() const {

    cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << "|" <<  setw(15) << "Airline" << endl;
    for (auto airport : script_.airportGraph_.getVertexSet()) {
        string airportCode = airport->getInfo().getAirportCode();
        string airportName= airport->getInfo().getAirportName();
        string city = airport->getInfo().getAirportCity();
        string airportCountry = airport->getInfo().getAirportCountry();

        cout << left << setw(4) << airportCode << "|" << setw(10) << airportName << "|" << setw(15) << city << "|" << setw(15) << airportCountry << "|" <<  setw(15) << endl;

    }

}

set<Airport> AirportManager::airportArticulationPoints() {

    Graph<Airport> undGraph;

    for (auto v : script_.airportGraph_.getVertexSet()) {
        undGraph.addVertex(v->getInfo());
    }

    for(auto v :  script_.airportGraph_.getVertexSet()) {
        for(const auto& edge : v->getAdj()) {
            auto dest = edge.getDest();
            undGraph.addEdge(v->getInfo(),dest->getInfo(),0, edge.getAirline());
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

Vertex<Airport> *const AirportManager::findClosestAirport(const position& targetPosition) const {
    // Initialize the closest airport and minimum distance variables
    auto closestAirport = script_.all_airports_.begin();
    double minDistance = closestAirport->second->getInfo().distance(targetPosition);

    auto iter = script_.all_airports_.begin();

    while (iter != script_.all_airports_.end()) {
        Airport currentAirport = iter->second->getInfo();
        double distance = currentAirport.distance(targetPosition);

        if (distance < minDistance) {
            minDistance = distance;
            closestAirport = iter;
        }

        ++iter;
    }

    return closestAirport->second;
}

int AirportManager::getAirportsNumber() const {
    return int(script_.all_airports_.size());
}

int AirportManager::getAirlinesNumber() const {
    return int(script_.all_airlines_.size());
}

int AirportManager::getFlightsNumber() const{
    return int(script_.all_flights_.size());
}

int AirportManager::getCitiesNumber() const{
    int counter = 0;
    for(const auto& country_cities : script_.cities_per_country_){
        counter += int(country_cities.second.size());
    }
    return counter;
}

int AirportManager::getCountriesNumber() const{
    return int(script_.cities_per_country_.size());
}

set<string> AirportManager::getCitiesInCountry(const string& country){
    auto it = script_.cities_per_country_.find(country);
    if(it == script_.cities_per_country_.end()){
        return {};
    }
    return it->second;
}

set<string> AirportManager::getCitiesInCountryWithAirport(const string& country) const{
    auto it = script_.cities_per_country_.find(country);
    if(it == script_.cities_per_country_.end()){
        return {};
    } else{
        return it->second;
    }
}

vector<Vertex<Airport>*> AirportManager::getAirportsPerCityAndCountry(const string& city, const string& country) const {
    auto it_city = script_.airports_per_city_and_country_.find(city);

    if(it_city == script_.airports_per_city_and_country_.end()) {
        return {};
    }

    auto& country_map = it_city->second;
    auto it_city_s_country = country_map.find(country);

    if(it_city_s_country == country_map.end()) {
        return {};
    }

    return it_city_s_country->second;
}

vector<Vertex<Airport>*> AirportManager::getAirportsPerCountry(const string& country) const {
    set<string> cities_set = getCitiesInCountryWithAirport(country);

    vector<Vertex<Airport>*> airports_in_country;

    for (const auto& city : cities_set) {
        auto new_airports = getAirportsPerCityAndCountry(city, country);
        airports_in_country.insert(airports_in_country.end(), new_airports.begin(), new_airports.end());
    }

    return airports_in_country;
}

int AirportManager::getNumberOfFlightsInAirline(const string& airline) const{
    auto it_airline = script_.all_airlines_.find(airline);
    if(it_airline == script_.all_airlines_.end()){
        return -1;
    }

    return it_airline->second.getAirlineNumberOfFlights();
}

set<pair<string, string>> AirportManager::getReachableAirports(const string &airport_name, int max_stops) {
    set<pair<string, string>> airports_set;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return airports_set;
    }

    vector<Vertex<Airport>*> airports_ptr_vertices = script_.airportGraph_.reachableAirports(airport->second, max_stops);

    for(auto& v : airports_ptr_vertices){
        airports_set.insert(make_pair(v->getInfo().getAirportCode(), v->getInfo().getAirportName()));
    }

    return airports_set;
}

set<string> AirportManager::getReachableCountries(const string& airport_name, int max_stops){
    set<string> countries;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return countries;
    }

    vector<Vertex<Airport>*> airports_ptr_vertices = script_.airportGraph_.reachableAirports(airport->second, max_stops);

    for(auto& v : airports_ptr_vertices){
        countries.insert(v->getInfo().getAirportCountry());
    }

    return countries;
}

set<pair<string, string>> AirportManager::getReachableCities(const string& airport_name, int max_stops){
    set<pair<string, string>> cities_countries;

    auto airport = script_.all_airports_.find(airport_name);

    if(airport == nullptr){
        return cities_countries;
    }

    vector<Vertex<Airport>*> airports_ptr_vertices = script_.airportGraph_.reachableAirports(airport->second, max_stops);

    for(auto& v : airports_ptr_vertices){
        cities_countries.insert(make_pair(v->getInfo().getAirportCity(), v->getInfo().getAirportCountry()));
    }

    return cities_countries;
}

vector<pair<pair<Vertex<Airport> *, Vertex<Airport> *>, int>> AirportManager::getMaximumTrip() {
    return script_.airportGraph_.maximumStops();
}

vector<pair<pair<Vertex<Airport> *, Vertex<Airport> *>, int>> AirportManager::getMaximumTripDiameter() {
    vector<destToSrcStopsPair> res;

    queue<pair<Vertex<Airport> *, int>> q;
    int maxDistance = 0;
    int curr = 0;
    Vertex<Airport>* lastV = nullptr;

    for(auto v : script_.airportGraph_.getVertexSet()) {
        curr = airportsDistanceBFSVisit(script_.airportGraph_, v, lastV, res, maxDistance);
        if( curr > maxDistance) {
            maxDistance = curr;
        }

    }
    return res;
}

int AirportManager::airportsDistanceBFSVisit(const Graph<Airport> &g, Vertex<Airport> *v1, Vertex<Airport>*& v2,   vector<destToSrcStopsPair>& res, int maxD) {

    queue<pair<Vertex<Airport> *, int>> q;

    g.resetIndegree();
    int dist;
    q.push({v1,0});

    v1->setVisited(true);

    while(!q.empty()) {
        auto currPair = q.front();
        q.pop();

        auto currVert = currPair.first;
        dist = currPair.second;

        for(auto& edge : currVert->getAdj()) {
            auto dest = edge.getDest();
            if(!dest->isVisited()) {
                v2 = dest;
                q.push({dest,dist+1});
                dest->setVisited(true);
                if( dist +1> maxD) {
                    maxD = dist +1;
                    res.clear();
                    res.push_back(make_pair(make_pair(v1,v2),dist+1));
                }
                else if (dist + 1 == maxD) {
                    res.push_back(make_pair(make_pair(v1,v2),dist+1));
                }

            }
        }

    }

    return dist;
}

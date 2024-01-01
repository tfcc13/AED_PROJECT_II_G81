#include <limits>
#include "Menu.h"

void waitEnter() {
    cout << endl << "Press enter to continue " << endl;
    string tmpString;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin,tmpString);
}

string getInput() {
    string input;
    cout << ">> ";
    cin >> input;
    cout << endl;
    return input;
}

template <typename T>
bool strToVar(const std::string &str, T &var){
    std::istringstream ss{str};
    ss >> var;
    if(ss.fail() || !ss.eof()){
        return false;
    }
    return true;
}

template <typename T>
bool get(T &var){
    std::string str = getInput();
    if(str.empty()){
        return false;
    }
    return strToVar(str, var);
}

Menu::Menu(Script &script) : script_(script) {}

Menu *Menu::invalidOption() {
    cout << "Invalid option. Please try again." << std::endl;
    waitEnter();
    return this;
}

FirstMenu::FirstMenu(Script &script) : Menu(script) {}

void FirstMenu::show() {
    int options = 0;

    cout << CLEAR;

    cout << R"(
      **********************************************************
      *          _    ___ ____ _____ _   _  ____    _          *
      *         / \  |_ _|  _ \_   _| | | |/ ___|  / \         *
      *        / _ \  | || |_) || | | | | | |  _  / _ \        *
      *       / ___ \ | ||  _ < | | | |_| | |_| |/ ___ \       *
      *      /_/   \_\___|_| \_\|_|  \___/ \____/_/   \_\      *
      **********************************************************
            )"  <<  "\n\n";

    cout << "MENU: \n\n";

    cout << "(" << ++options << ") >> " << "Go to General Information Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to airport Information Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to Best flight Option Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to Best flight Option with Filters Menu" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;

}

Menu *FirstMenu::getNextMenu() {
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    switch (option) {
        case 0:
            return nullptr;
        case 1:
            return new GeneralInformationMenu(script_);
        case 2:
            return new AirportInformationMenu(script_);
        case 3:
            return new BestFlightMenu(script_);
    }

    return invalidOption();
}

GeneralInformationMenu::GeneralInformationMenu(Script &script) : Menu(script) {}

void GeneralInformationMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check the number of airports in the database" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of airlines in the database" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of flights in the database" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of cities in the database" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of countries in the database" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of cities in a country in the current database" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;
}

Menu *GeneralInformationMenu::getNextMenu() {
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;
    switch (option) {
        case 0:
            return nullptr;

        case 1:
            cout << "There are " + to_string(airportManager.getAirportsNumber()) + " airports available!" << endl;
            cout << endl;
            break;

        case 2:
            cout << "There are " << airportManager.getAirlinesNumber() << " airlines available!" << endl;
            cout << endl;
            break;

        case 3:
            cout << "There are " << airportManager.getFlightsNumber() << " flights available" << endl;
            cout << endl;
            break;

        case 4:
            cout << "There are " << airportManager.getCitiesNumber() << " cities available" << endl;
            cout << endl;
            break;

        case 5:
            cout << "There are " << airportManager.getCountriesNumber() << " countries available" << endl;
            cout << endl;
            break;

        case 6:
            cout << "Please write the country's name" << endl;
            cout << endl;
            input = getInput();
            auto cities = airportManager.getCitiesInCountry(input);
            if(cities.empty()){
                cout << input << "isn't is the database";
            } else{
                cout << "There are " << int(cities.size()) << " cities available in " << input << endl;
                cout << endl;
                cout << "Do you wish to see the city names? Press 'y' for yes or 'n' for no" << endl;
                cout << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    for(const auto& city : cities){
                        cout << city << endl;
                    }
                    cout << endl;
                }
            }
            break;

    }

    waitEnter();

    return this;
}

AirportInformationMenu::AirportInformationMenu(Script &script) : Menu(script) {}

void AirportInformationMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check how many flights/airlines/cities/countries DEPART from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many flights/airlines/cities/countries ARRIVE from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check the total number of flights for a given city, considering both departures and arrivals at every airport in the city" << endl;
    cout << "(" << ++options << ") >> " << "Check the total number of flights for a given airline" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable cities/countries/airports from a given airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the airports with the greatest air traffic capacity" << endl;
    cout << "(" << ++options << ") >> " << "See the airports essential to the network's circulation capability" << endl;
    cout << "(" << ++options << ") >> " << "See the maximum trip, or trips, available in this airport network" << endl;
    cout << "(" << ++options << ") >> " << "See the maximum trip, or trips, diameter in this airport network" << endl;
    cout << "(" << ++options << ") >> " << "See all airports" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;
}

Menu *AirportInformationMenu::getNextMenu() {
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;
    switch (option) {
        case 0:
            return nullptr;

        case 1: {
            return new AirportDeparturesMenu(script_);
        }

        case 2: {
            return new AirportArrivalsMenu(script_);
        }

        case 3: {
            cout << "Please write the name of the city" << endl;
            cout << endl;
            string city = getInput();
            cout << "Please write the name of the country (only the city name may be ambiguous)" << endl;
            cout << endl;
            string country = getInput();
            int number_of_flights = airportManager.getFlightsPerCity(city, country);
            if(number_of_flights == -1){
                cout << "Name of the city/country not found in Airtuga's database";
                break;
            }
            cout << number_of_flights << " flights are performed in " << city << " city" << endl;
            cout << endl;
            break;
        }

        case 4: {
            cout << "Please write the name of the airline" << endl;
            cout << endl;
            string airline = getInput();
            int number_of_flights = airportManager.getFlightsPerAirline(airline);
            cout << number_of_flights << " flights are performed by " << airline << "airline" << endl;
            if(number_of_flights == -1){
                cout << "Name of the airline not found in Airtuga's database";
                break;
            }
            cout << endl;
            break;
        }

        case 5: {
            return new ReachableFromXStops(script_);
        }

        case 6: {
            cout << "Please write the number of airports you want to see" << endl;
            cout << endl;
            int k;
            if(!get(k)) {
                return invalidOption();
            }

            vector<pair<Airport, int>> topKAirports = airportManager.getTopKAiportTrafficCap(k);

            cout << left << setw(4) << "Code" << "|" << setw(15) << "Name" << "|" << "flights" << endl;

            for (auto airport = topKAirports.begin(); airport != topKAirports.end(); airport++) {

                cout << left << setw(4) << airport->first.getAirportCode() << "|" << setw(15) << airport->first.getAirportName() << "|" << airport->second << endl;
            }

            cout << endl;
            break;
        }

        case 7: {
            set<Airport> essentialAirports = airportManager.airportArticulationPoints();
            cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "city" << "|" << setw(15) << "country" << endl;

            for(const auto& airport: essentialAirports) {
                cout << left << setw(4) << airport.getAirportCode() << "|" << setw(10) << airport.getAirportName() << "|" << setw(15) << airport.getAirportCity() << "|" << setw(15) << airport.getAirportCountry() << endl;
            }
            cout << endl;

            cout << "It has " << essentialAirports.size() << " essential airports to the network's circulation capability" << endl;
            cout << endl ;
            break;
        }

        case 8: {
            vector<pair<pair<Vertex<Airport> *, Vertex<Airport> *>, int>> maxTripVector = airportManager.getMaximumTrip();
            cout << left << setw(4) << "Source airport Code" << "|" << setw(15) << "Source airport Name" << "|" << setw(4) << "Dest. airport Code" << "|" << setw(15) << "Dest airport Name" << "|" << "Number of Stops" << endl;

            for(const auto& p: maxTripVector) {
                cout << left << setw(4) << p.first.first->getInfo().getAirportCode() << "|" << setw(15) << p.first.first->getInfo().getAirportName() << "|" << setw(4) << p.first.second->getInfo().getAirportCode() << "|" << setw(15) << p.first.second->getInfo().getAirportName() << "|" << p.second<< endl;
            }
            cout << endl;

            cout << "It has " <<  maxTripVector.size() << " maximum trips available" << endl;
            cout << endl ;
            break;
        }

        case 9: {
            vector<pair<pair<Vertex<Airport> *, Vertex<Airport> *>, int>> maxTripVector = airportManager.getMaximumTripDiameter();
            cout << left << setw(4) << "Source airport Code" << "|" << setw(15) << "Source airport Name" << "|" << setw(4) << "Dest. airport Code" << "|" << setw(15) << "Dest airport Name" << "|" << "Number of Stops" << endl;

            for(const auto& p: maxTripVector) {
                cout << left << setw(4) << p.first.first->getInfo().getAirportCode() << "|" << setw(15) << p.first.first->getInfo().getAirportName() << "|" << setw(4) << p.first.second->getInfo().getAirportCode() << "|" << setw(15) << p.first.second->getInfo().getAirportName() << "|" << p.second<< endl;
            }
            cout << endl;

            cout << "It has " <<  maxTripVector.size() << " maximum trips available" << endl;
            cout << endl ;
            break;
        }
        case 10: {
            airportManager.printAllAirports();
            cout << endl;
            break;
        }

    }

    waitEnter();
    return this;

}

AirportDeparturesMenu::AirportDeparturesMenu(Script &script) : Menu(script){}

void AirportDeparturesMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check how many flights DEPART from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many airlines DEPART from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many cities DEPART from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many countries DEPART from a given airport" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;
}

Menu *AirportDeparturesMenu::getNextMenu(){
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;

    switch (option) {
        case 0: {
            return nullptr;
        }

        case 1: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int flightsCount = airportManager.getAirportFlightsNumber(input, "departures");

            if (flightsCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
                break;
            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << flightsCount << " flights departing from " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the flights data? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getAirportsFlightsData(input, "departures");
                }
            }
            break;
        }

        case 2: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int airlinesCount = airportManager.getAirportAirlinesNumber(input, "departures");

            if (airlinesCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;

            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << airlinesCount << " airlines departing from " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.printAirlinesNames(input, "departures");
                }
                break;
            }

            break;
        }

        case 3: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int citiesCount = airportManager.getDestinationCitiesNumber(input, "departures");

            if (citiesCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << citiesCount  << " cities that you can fly to from the " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCitiesNames(input, "departures");
                }
                break;
            }
            break;
        }

        case 4: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int countriesCount = airportManager.getDestinationCountriesNumber(input, "departures");

            if (countriesCount== -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << countriesCount << " destination countries that you can fly to from the " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the destination countries ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCountriesNames(input, "departures");
                    cout << "Be aware that there may be domestic flights." << endl;
                    cout << "The source country can be also a destination country." << endl;
                }
                break;
            }
            break;
        }

    }

    waitEnter();
    return this;

}

AirportArrivalsMenu::AirportArrivalsMenu(Script &script) : Menu(script){}

void AirportArrivalsMenu::show(){
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check how many airlines ARRIVE from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many flights ARRIVE from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many cities ARRIVE from a given airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many countries ARRIVE from a given airport" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;
}

Menu *AirportArrivalsMenu::getNextMenu(){
    
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;

    switch (option) {
        case 0: {
            return nullptr;
        }

        case 1: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int flightsCount = airportManager.getAirportFlightsNumber(input, "arrivals");

            if (flightsCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
                break;
            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << flightsCount << " flights arriving at " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the flights data? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getAirportsFlightsData(input, "arrivals");
                }
            }
            break;
        }

        case 2: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int airlinesCount = airportManager.getAirportAirlinesNumber(input, "arrivals");

            if (airlinesCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;

            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << airlinesCount << " airlines arriving at " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.printAirlinesNames(input, "arrivals");
                }
                break;
            }

            break;
        }

        case 3: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int citiesCount = airportManager.getDestinationCitiesNumber(input, "arrivals");

            if (citiesCount == -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << citiesCount  << " cities that fly to the " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCitiesNames(input, "arrivals");
                }
                break;
            }
            break;
        }

        case 4: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();

            int countriesCount = airportManager.getDestinationCountriesNumber(input, "arrivals");

            if (countriesCount== -1) {
                cout << "That airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << countriesCount << " countries that fly to the " << airportName << " airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the destination countries ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCountriesNames(input, "arrivals");
                    cout << "Be aware that there may be domestic flights." << endl;
                    cout << "The source country can be also a destination country." << endl;
                }
                break;
            }
            break;
        }

    }

    waitEnter();
    return this;

}

ReachableFromXStops::ReachableFromXStops(Script &script) : Menu(script){}

void ReachableFromXStops::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check the number of reachable cities from a given airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable countries from a given airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable airports from a given airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;
}

Menu * ReachableFromXStops::getNextMenu(){
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;

    switch (option) {

        case 0: {
            return nullptr;
        }

        case 1: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();
            cout << "Please write the maximum number of stops" << endl;
            int max_stops;
            if(!get(max_stops)) {
                return invalidOption();
            }
            if(max_stops <= 0){
                cout << "Invalid maximum number of stops. The number must be greater than 0!";
                break;
            } else{
                set<pair<string, string>> reachable_cities = airportManager.getReachableCities(input, max_stops);
                cout << "There are " << int(reachable_cities.size()) << " cities reachable from " << input << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the names of reachable cities? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    cout << left << setw(35) << "city" << " | " << "country" << endl << endl;
                    for(const auto& city_country : reachable_cities){
                        cout << left << setw(35) << city_country.first << " | " << city_country.second << endl;
                    }
                }
            }
            break;
        }

        case 2: {
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();
            cout << "Please write the maximum number of stops" << endl;
            int max_stops;
            if(!get(max_stops)) {
                return invalidOption();
            }
            if(max_stops <= 0){
                cout << "Invalid maximum number of stops. The number must be greater than 0!";
                break;
            } else{
                set<string> reachable_countries = airportManager.getReachableCountries(input, max_stops);
                cout << "There are " << int(reachable_countries.size()) << " countries reachable from " << input << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the names of reachable countries? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    cout << left << setw(35) << "country" << endl << endl;
                    for(const auto& country : reachable_countries){
                        cout << left << country << endl;
                    }
                }
            }
            break;
        }

        case 3:{
            cout << "Please write the airport code" << endl;
            cout << endl;
            input = getInput();
            cout << "Please write the maximum number of stops" << endl;
            int max_stops;
            if(!get(max_stops)) {
                return invalidOption();
            }
            if(max_stops <= 0){
                cout << "Invalid maximum number of stops. The number must be greater than 0!";
                break;
            } else{
                set<pair<string, string>> reachable_airports = airportManager.getReachableAirports(input, max_stops);
                cout << "There are " << int(reachable_airports.size()) << " airports reachable from " << input << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the names of reachable airports? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    cout << left << setw(15) << "airport code" << " | " << "airport name" << endl << endl;
                    for(const auto& airport : reachable_airports){
                        cout << left << setw(15) << airport.first << " | " << airport.second << endl;
                    }
                }
            }
            break;
        }

    }

    waitEnter();
    return this;

}

BestFlightMenu::BestFlightMenu(Script &script) : Menu(script) {}

void BestFlightMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Find the best flight from airport to airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from airport to city" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from airport to Position" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from city to airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from city to city" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from city to Position" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Position to airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Position to city" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Position to Position" << endl;
    cout << "(0) >> Exit " << endl;
    cout << endl;
}

Menu *BestFlightMenu::getNextMenu() {
    int option;

    if (!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;

    switch (option) {
        case 0:
            return nullptr;

        case 1:
            string depAirportCode, destAirportCode;
            cout << "Enter the airport codes for departure and destination airports: " << endl;
            cin >> depAirportCode >> destAirportCode;
            Vertex<Airport>* depAirport = script_.getAllAirports().find(depAirportCode)->second;
            Vertex<Airport>* destAirport = script_.getAllAirports().find(destAirportCode)->second;
            cout << endl;
            auto path = script_.getAirportGraph().shortestPath(depAirport, destAirport);
            if (path.empty()) cout << "There is no possible path.";
            else {
                cout << "The best path is:" << endl;
                for (auto a : path) {
                    cout << a.getAirportCode() << endl;
                }
                cout << endl;
            }
            cout << endl;
            break;

            /*
        case 2:
            // Logic for finding the best flight from airport to city
            // Implement the necessary functionality here
            break;

        case 3:
            // Logic for finding the best flight from airport to Position
            // Implement the necessary functionality here
            break;

        case 4:
            // Logic for finding the best flight from city to airport
            // Implement the necessary functionality here
            break;

        case 5:
            // Logic for finding the best flight from city to city
            // Implement the necessary functionality here
            break;

        case 6:
            // Logic for finding the best flight from city to Position
            // Implement the necessary functionality here
            break;

        case 7:
            // Logic for finding the best flight from Position to airport
            // Implement the necessary functionality here
            break;

        case 8:
            // Logic for finding the best flight from Position to city
            // Implement the necessary functionality here
            break;

        case 9:
            // Logic for finding the best flight from Position to Position
            // Implement the necessary functionality here
            break;

             */
    }


    waitEnter();
    return this;
}

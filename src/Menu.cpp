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
    cout << "(" << ++options << ") >> " << "Go to Airport Information Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to Best Flight Option Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to Best Flight Option with Filters Menu" << endl;
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
    cout << "(" << ++options << ") >> " << "Check how many Airports there are" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airlines  there are" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Flights there are" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Flights there are from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airlines there are in a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many cities you can fly to from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airports you can fly to from a given Airport" << endl;
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
            cout << "There are " + to_string(airportManager.getAirportsNumber()) + " Airports available!" << endl;
            cout << endl;
            break;
        case 2:
            cout << "There are " << airportManager.getAirlinesNumber() << " Airlines available!" << endl;
            cout << endl;
            break;
        case 3:
            cout << "There are " << script_.getFlightsSet().size() << " Flights available" << endl;
            cout << endl;
            break;

    }

    waitEnter();

    return this;
}

AirportInformationMenu::AirportInformationMenu(Script &script) : Menu(script) {}

void AirportInformationMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check how many Flights there are from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airlines there are in a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many cities you can fly to from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many countries you can fly to from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airports you can fly to from a given Airport" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable cities from a given Airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable countries from a given Airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the number of reachable Airports from a given Airport in a maximum number of X stops (lay-overs)" << endl;
    cout << "(" << ++options << ") >> " << "Check the Airports with the greatest air traffic capacity" << endl;
    cout << "(" << ++options << ") >> " << "See the airports essential to the network's circulation capability" << endl;
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

            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int flightsCount = airportManager.getAirportFlightsNumber(input);

            if (flightsCount == -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
                break;
            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << flightsCount << " Flights available from " << airportName << " Airport" << endl;
                cout << endl;
                cout << "Do you wish to see the Flights data? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getAirportsFlightsData(input);
                }
            }
            break;
        }
        case 2: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int airlinesCount = airportManager.getAirportAirlinesNumber(input);

            if (airlinesCount == -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;

            } else {
                string airportName = airportManager.getAirportName(input);
                cout << "There are " << airlinesCount << " airlines flying from " << airportName << " Airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.printAirlinesNames(input);
                }
                break;
            }

            break;
        }
        case 3: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int citiesCount = airportManager.getDestinationCitiesNumber(input);

            if (citiesCount == -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << citiesCount  << " cities that you can fly to from the " << airportName << " Airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the cities ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCitiesNames(input);
                }
                break;
            }
            break;
        }
        case 4: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int countriesCount = airportManager.getDestinationCountriesNumber(input);

            if (countriesCount== -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << countriesCount << " destination countries that you can fly to from the " << airportName << " Airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the destination countries ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationCountriesNames(input);
                    cout << "Be aware that there may be domestic flights." << endl;
                    cout << "The source country can be also a destination country." << endl;
                }
                break;
            }
            break;
        }

        case 5: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();
            cout << "Please write the maximum number of stops" << endl;
            cout << endl << ">> ";
            int max_stops;
            cin >> max_stops;
            if(max_stops <= 0){
                cout << "Invalid maximum number of stops. The number must be greater than 0!";
                break;
            } else{
                set<pair<string, string>> reachable_cities = airportManager.getReachableCities(input, max_stops);
                cout << "There are " << int(reachable_cities.size()) << " cities reachable from " << input << " airport" << endl;
                cout << endl;
                cout << "Do you wish to see the names of reachable cities? Press 'y' for yes or 'n' for no";
            }
            break;
        }

        case 6: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();
        }

        case 7: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();
        }

        case 8: {
            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int airportCount = airportManager.getDestinationAirportsNumber(input);

            if (airportCount == -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
            } else {

                string airportName = airportManager.getAirportName(input);
                cout << "There are " << airportCount  << " destination Airports that you can fly to from the " << airportName << " Airport" << endl;
                cout << endl;
                cout << "Do you wish to know the names of the destination Airports ? Press 'y' for yes or 'n' for no" << endl;
                string ans = getInput();
                if(ans == "y" || ans == "Y") {
                    airportManager.getDestinationAirportsNames(input);
                    cout << endl;


                }
                break;
            }
            break;
        }

        case 9: {
            cout << "Please write the number of Airports you want to see" << endl;
            cout << endl;
            int k;
            if(!get(k)) {
                return invalidOption();
            }

            vector<pair<Airport, int>> topKAirports = airportManager.getTopKAiportTrafficCap(k);

            cout << left << setw(4) << "Code" << "|" << setw(15) << "Name" << "|" << "Flights" << endl;

            for (auto airport = topKAirports.begin(); airport != topKAirports.end(); airport++) {

                cout << left << setw(4) << airport->first.getAirportCode() << "|" << setw(15) << airport->first.getAirportName() << "|" << airport->second << endl;
            }

        cout << endl;
        break;
        }
        case 10: {
            set<Airport> essentialAirports = airportManager.airportArticulationPoints();
            cout << left << setw(4) << "Code" << "|" << setw(10) << "Name" << "|" << setw(15) << "City" << "|" << setw(15) << "Country" << endl;

            for(const auto& airport: essentialAirports) {
                cout << left << setw(4) << airport.getAirportCode() << "|" << setw(10) << airport.getAirportName() << "|" << setw(15) << airport.getAirportCity() << "|" << setw(15) << airport.getAirportCountry() << endl;
            }
            cout << endl;

            cout << "It has " << essentialAirports.size() << " essential airports to the network's circulation capability" << endl;
            cout << endl ;
            break;
        }
        case 11: {
            airportManager.printAllAirports();
            cout << endl;
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
    cout << "(" << ++options << ") >> " << "Find the best flight from Airport to Airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Airport to City" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Airport to Position" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from City to Airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from City to City" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from City to Position" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Position to Airport" << endl;
    cout << "(" << ++options << ") >> " << "Find the best flight from Position to City" << endl;
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
            cout << "Enter the Airport codes for departure and destination Airports: " << endl;
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
            // Logic for finding the best flight from Airport to City
            // Implement the necessary functionality here
            break;

        case 3:
            // Logic for finding the best flight from Airport to Position
            // Implement the necessary functionality here
            break;

        case 4:
            // Logic for finding the best flight from City to Airport
            // Implement the necessary functionality here
            break;

        case 5:
            // Logic for finding the best flight from City to City
            // Implement the necessary functionality here
            break;

        case 6:
            // Logic for finding the best flight from City to Position
            // Implement the necessary functionality here
            break;

        case 7:
            // Logic for finding the best flight from Position to Airport
            // Implement the necessary functionality here
            break;

        case 8:
            // Logic for finding the best flight from Position to City
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

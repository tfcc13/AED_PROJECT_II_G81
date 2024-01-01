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
        case 4:
            return new BestFlightWithFiltersMenu(script_);
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
                    airportManager.PrintAirlinesNames(input);
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

        case 6: {
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
        case 7: {
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
        case 8: {
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
        case 0: {return nullptr;}

        case 1: {
            string depAirportCode, destAirportCode;
            cout << "Enter the Airport codes for departure and destination Airports: " << endl;
            cin >> depAirportCode >> destAirportCode;

            // Retrieve the vertices (airports) if they exist, otherwise nullptr
            Vertex<Airport> *depAirport = nullptr;
            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            auto destAirportIter = allAirports.find(destAirportCode);

            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }

            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }

            // Check for invalid input
            if (depAirport == nullptr || destAirport == nullptr) {
                cout << "Invalid airport code(s) entered." << endl;
            } else {
                cout << endl;
                auto paths = script_.getAirportGraph().allShortestPaths(depAirport, destAirport);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

        case 2: {
            string depAirportCode, country, city;

            cout << "Enter the Airport code for departure:" << endl;

            cin >> depAirportCode;
            cin.ignore(); // Clear the input buffer

            cout << "Enter the destination City: " << endl;
            getline(cin, city);

            cout << "Enter that city's Country: " << endl;
            getline(cin, country);


            // Retrieve the vertices (airports) if they exist, otherwise nullptr
            Vertex<Airport> *depAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }

            if (depAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (destAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                vector<vector<Edge<Airport>>> paths;
                for (auto airport: destAirports) {
                    for (auto path : script_.getAirportGraph().allShortestPaths(depAirport, airport)) paths.push_back(path);
                }

                int size = INT_MAX;
                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                // Iterate through the vectors to find the shortest one
                for (vector<Edge<Airport>> path : paths) {
                    if (path.size() < size) {
                        size = path.size();
                        shortestPaths.clear();
                        shortestPaths.push_back(path);
                    }
                    if (path.size() == size) shortestPaths.push_back(path);
                }

                airportManager.printPaths(shortestPaths, depAirport);
            }

        } break;

        case 3: {
            string depAirportCode;
            double lat, lon;

            cout << "Enter the Airport code for departure and destination Position (Latitude and Longitude, as double):" << endl;

            cin >> depAirportCode >> lat >> lon;

            Vertex<Airport> *depAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }



            if (depAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else {
                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport to destination is " << destAirport->getInfo().getAirportCode() << endl;

                auto paths = script_.getAirportGraph().allShortestPaths(depAirport, destAirport);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

        case 4: {
            string destAirportCode, country, city;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, city);
            cin.ignore();

            cout << "Enter that city's Country: " << endl;
            getline(cin >> ws, country);
            cin.ignore();

            cout << "Enter the destination Airport code:" << endl;
            cin >> destAirportCode;
            cin.ignore();


            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto destAirportIter = allAirports.find(destAirportCode);
            auto depAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }

            if (destAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (depAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                unordered_map<Vertex<Airport>*, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto airport: depAirports) {
                    vector<vector<Edge<Airport>>> paths;
                    for (auto path: script_.getAirportGraph().allShortestPaths(airport, destAirport))
                        paths.push_back(path);
                    startingPoints[airport] = paths;
                }

                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }


                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }


        } break;

        case 5: {
            string depCity, depCountry, destCity, destCountry;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, depCity);

            cout << "Enter the departure Country: " << endl;
            getline(cin >> ws, depCountry);

            cout << "Enter the destination City: " << endl;
            getline(cin >> ws, destCity);

            cout << "Enter the destination Country: " << endl;
            getline(cin >> ws, destCountry);


            auto depAirports = airportManager.getAirportsPerCityAndCountry(depCity, depCountry);
            auto destAirports = airportManager.getAirportsPerCityAndCountry(destCity, destCountry);

            if (depAirports.empty() || destAirports.empty()) {
                cout << "No airports found in one or both of the cities." << endl;
            } else {
                unordered_map<Vertex<Airport> *, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto depAirport: depAirports) {
                    for (auto destAirport: destAirports) {
                        vector<vector<Edge<Airport>>> paths;
                        for (auto path: script_.getAirportGraph().allShortestPaths(depAirport, destAirport))
                            paths.push_back(path);
                        startingPoints[depAirport] = paths;
                    }
                }



                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }

                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }

        } break;

        case 6: {

            string country, city;
            double lat, lon;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, city);
            cin.ignore();

            cout << "Enter that city's Country: " << endl;
            getline(cin >> ws, country);
            cin.ignore();

            cout << "Enter destination Position (Latitude and Longitude, as double):" << endl;
            cin >> lat >> lon;
            cin.ignore();

            auto depAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else if (depAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {

                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport to destination is " << destAirport->getInfo().getAirportCode() << endl;

                unordered_map<Vertex<Airport>*, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto airport: depAirports) {
                    vector<vector<Edge<Airport>>> paths;
                    for (auto path: script_.getAirportGraph().allShortestPaths(airport, destAirport))
                        paths.push_back(path);
                    startingPoints[airport] = paths;
                }

                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }


                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }



        } break;

        case 7: {
            double lat, lon;
            string destAirportCode;

            cout << "Enter departure Position (Latitude and Longitude, as double) and destination Airport:" << endl;

            cin >> lat >> lon >> destAirportCode;

            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto destAirportIter = allAirports.find(destAirportCode);
            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }



            if (destAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;

                auto paths = script_.getAirportGraph().allShortestPaths(depAirport, destAirport);
                airportManager.printPaths(paths, depAirport);
            }


        } break;

        case 8: {
            double lat, lon;
            string country, city;

            cout << "Enter departure Position (Latitude and Longitude, as double):" << endl;

            cin >> lat >> lon;
            cin.ignore(); // Clear the input buffer

            cout << "Enter the destination City: " << endl;
            getline(cin, city);

            cout << "Enter that city's Country: " << endl;
            getline(cin, country);


            auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else if (destAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;
                auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

                vector<vector<Edge<Airport>>> paths;
                for (auto airport: destAirports) {
                    for (auto path : script_.getAirportGraph().allShortestPaths(depAirport, airport)) paths.push_back(path);
                }

                int size = INT_MAX;
                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                // Iterate through the vectors to find the shortest one
                for (vector<Edge<Airport>> path : paths) {
                    if (path.size() < size) {
                        size = path.size();
                        shortestPaths.clear();
                        shortestPaths.push_back(path);
                    }
                    if (path.size() == size) shortestPaths.push_back(path);
                }

                airportManager.printPaths(shortestPaths, depAirport);
            }
        } break;

        case 9: {
            double lat1, lon1, lat2, lon2;

            cout << "Enter departure and destination Positions (Latitude and Longitude, as double):" << endl;
            cin >> lat1 >> lon1 >> lat2 >> lon2;

            if (!(-90 < lat1 && lat1 < 90 && -180 < lon1 && lon1 < 180 && -90 < lat2 && lat2 < 90 && -180 < lon2 && lon2 < 180)) {
                cout << "Invalid coordinate(s) entered." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat1, lon1});
                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat2, lon2});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;
                cout << "Closest airport for arrival is " << destAirport->getInfo().getAirportCode() << endl;
                cout << endl;

                auto paths = script_.getAirportGraph().allShortestPaths(depAirport, destAirport);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

    }


    waitEnter();
    return this;
}
















BestFlightWithFiltersMenu::BestFlightWithFiltersMenu(Script &script) : Menu(script) {}



void BestFlightWithFiltersMenu::show() {
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

Menu *BestFlightWithFiltersMenu::getNextMenu() {
    int option;

    if (!get(option)) {
        return invalidOption();
    }

    AirportManager airportManager(script_);
    string input;

    switch (option) {
        case 0: {return nullptr;}

        case 1: {
            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }


            string depAirportCode, destAirportCode;
            cout << "Enter the Airport codes for departure and destination Airports: " << endl;
            cin >> depAirportCode >> destAirportCode;


            // Retrieve the vertices (airports) if they exist, otherwise nullptr
            Vertex<Airport> *depAirport = nullptr;
            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            auto destAirportIter = allAirports.find(destAirportCode);

            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }

            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }

            // Check for invalid input
            if (depAirport == nullptr || destAirport == nullptr) {
                cout << "Invalid airport code(s) entered." << endl;
            } else {
                cout << endl;
                auto paths = script_.getAirportGraph().allShortestPathsWithFilter(depAirport, destAirport, filter);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

        case 2: {
            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }


            string depAirportCode, country, city;

            cout << "Enter the Airport code for departure:" << endl;

            cin >> depAirportCode;
            cin.ignore(); // Clear the input buffer

            cout << "Enter the destination City: " << endl;
            getline(cin, city);

            cout << "Enter that city's Country: " << endl;
            getline(cin, country);



            // Retrieve the vertices (airports) if they exist, otherwise nullptr
            Vertex<Airport> *depAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }

            if (depAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (destAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                vector<vector<Edge<Airport>>> paths;
                for (auto airport: destAirports) {
                    for (auto path : script_.getAirportGraph().allShortestPathsWithFilter(depAirport, airport, filter)) paths.push_back(path);
                }

                int size = INT_MAX;
                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                // Iterate through the vectors to find the shortest one
                for (vector<Edge<Airport>> path : paths) {
                    if (path.size() < size) {
                        size = path.size();
                        shortestPaths.clear();
                        shortestPaths.push_back(path);
                    }
                    if (path.size() == size) shortestPaths.push_back(path);
                }

                airportManager.printPaths(shortestPaths, depAirport);
            }

        } break;

        case 3: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }

            string depAirportCode;
            double lat, lon;

            cout << "Enter the Airport code for departure and destination Position (Latitude and Longitude, as double):" << endl;

            cin >> depAirportCode >> lat >> lon;



            Vertex<Airport> *depAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto depAirportIter = allAirports.find(depAirportCode);
            if (depAirportIter != allAirports.end()) {
                depAirport = depAirportIter->second;
            }



            if (depAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else {
                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport to destination is " << destAirport->getInfo().getAirportCode() << endl;

                auto paths = script_.getAirportGraph().allShortestPathsWithFilter(depAirport, destAirport, filter);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

        case 4: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }

            string destAirportCode, country, city;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, city);
            cin.ignore();

            cout << "Enter that city's Country: " << endl;
            getline(cin >> ws, country);
            cin.ignore();

            cout << "Enter the destination Airport code:" << endl;
            cin >> destAirportCode;
            cin.ignore();


            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto destAirportIter = allAirports.find(destAirportCode);
            auto depAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }

            if (destAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (depAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                unordered_map<Vertex<Airport>*, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto airport: depAirports) {
                    vector<vector<Edge<Airport>>> paths;
                    for (auto path: script_.getAirportGraph().allShortestPathsWithFilter(airport, destAirport, filter))
                        paths.push_back(path);
                    startingPoints[airport] = paths;
                }

                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }


                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }


        } break;

        case 5: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }


            string depCity, depCountry, destCity, destCountry;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, depCity);

            cout << "Enter the departure Country: " << endl;
            getline(cin >> ws, depCountry);

            cout << "Enter the destination City: " << endl;
            getline(cin >> ws, destCity);

            cout << "Enter the destination Country: " << endl;
            getline(cin >> ws, destCountry);


            auto depAirports = airportManager.getAirportsPerCityAndCountry(depCity, depCountry);
            auto destAirports = airportManager.getAirportsPerCityAndCountry(destCity, destCountry);

            if (depAirports.empty() || destAirports.empty()) {
                cout << "No airports found in one or both of the cities." << endl;
            } else {
                unordered_map<Vertex<Airport> *, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto depAirport: depAirports) {
                    for (auto destAirport: destAirports) {
                        vector<vector<Edge<Airport>>> paths;
                        for (auto path: script_.getAirportGraph().allShortestPathsWithFilter(depAirport, destAirport, filter))
                            paths.push_back(path);
                        startingPoints[depAirport] = paths;
                    }
                }



                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }

                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }

        } break;

        case 6: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }

            string country, city;
            double lat, lon;

            cout << "Enter the departure City: " << endl;
            getline(cin >> ws, city);
            cin.ignore();

            cout << "Enter that city's Country: " << endl;
            getline(cin >> ws, country);
            cin.ignore();

            cout << "Enter destination Position (Latitude and Longitude, as double):" << endl;
            cin >> lat >> lon;
            cin.ignore();


            auto depAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else if (depAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {

                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport to destination is " << destAirport->getInfo().getAirportCode() << endl;

                unordered_map<Vertex<Airport>*, vector<vector<Edge<Airport>>>> startingPoints;
                for (auto airport: depAirports) {
                    vector<vector<Edge<Airport>>> paths;
                    for (auto path: script_.getAirportGraph().allShortestPathsWithFilter(airport, destAirport, filter))
                        paths.push_back(path);
                    startingPoints[airport] = paths;
                }

                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                int size = INT_MAX;
                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize < size) {
                            size = pathSize;
                        }
                    }
                }

                for (auto& pair : startingPoints) {
                    vector<vector<Edge<Airport>>>& paths = pair.second;

                    vector<vector<Edge<Airport>>> shortestPathsForAirport;


                    for (const auto& path : paths) {
                        int pathSize = path.size();
                        if (pathSize == size) {
                            shortestPathsForAirport.push_back(path);
                        }
                    }

                    paths = shortestPathsForAirport;
                }


                for (auto& pair : startingPoints) {
                    cout << "Paths starting in " << pair.first->getInfo().getAirportCode() << ":" << endl;
                    airportManager.printPaths(pair.second, pair.first);
                }
            }



        } break;

        case 7: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }

            double lat, lon;
            string destAirportCode;

            cout << "Enter departure Position (Latitude and Longitude, as double) and destination Airport:" << endl;

            cin >> lat >> lon >> destAirportCode;



            Vertex<Airport> *destAirport = nullptr;

            auto allAirports = script_.getAllAirports();
            auto destAirportIter = allAirports.find(destAirportCode);
            if (destAirportIter != allAirports.end()) {
                destAirport = destAirportIter->second;
            }



            if (destAirport == nullptr) {
                cout << "Invalid airport code entered." << endl;
            } else if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;

                auto paths = script_.getAirportGraph().allShortestPathsWithFilter(depAirport, destAirport, filter);
                airportManager.printPaths(paths, depAirport);
            }


        } break;

        case 8: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }


            double lat, lon;
            string country, city;

            cout << "Enter departure Position (Latitude and Longitude, as double):" << endl;

            cin >> lat >> lon;
            cin.ignore(); // Clear the input buffer

            cout << "Enter the destination City: " << endl;
            getline(cin, city);

            cout << "Enter that city's Country: " << endl;
            getline(cin, country);


            auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

            if (!(-90 < lat && lat < 90 && -180 < lon && lon < 180)) {
                cout << "Invalid coordinate entered." << endl;
            } else if (destAirports.empty()) {
                cout << "No airports found in that city." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat, lon});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;
                auto destAirports = airportManager.getAirportsPerCityAndCountry(city, country);

                vector<vector<Edge<Airport>>> paths;
                for (auto airport: destAirports) {
                    for (auto path : script_.getAirportGraph().allShortestPathsWithFilter(depAirport, airport, filter)) paths.push_back(path);
                }

                int size = INT_MAX;
                vector<vector<Edge<Airport>>> shortestPaths;
                cout << endl;

                // Iterate through the vectors to find the shortest one
                for (vector<Edge<Airport>> path : paths) {
                    if (path.size() < size) {
                        size = path.size();
                        shortestPaths.clear();
                        shortestPaths.push_back(path);
                    }
                    if (path.size() == size) shortestPaths.push_back(path);
                }

                airportManager.printPaths(shortestPaths, depAirport);
            }
        } break;

        case 9: {

            cin.ignore();
            unordered_set<string> filter;
            string input;

            cout << "Enter airlines that can be part of your path (press Enter when finished):" << endl;
            getline(cin, input);

            istringstream iss(input);
            string airline;

            while (iss >> airline) {
                filter.insert(airline);
            }


            double lat1, lon1, lat2, lon2;

            cout << "Enter departure and destination Positions (Latitude and Longitude, as double):" << endl;
            cin >> lat1 >> lon1 >> lat2 >> lon2;


            if (!(-90 < lat1 && lat1 < 90 && -180 < lon1 && lon1 < 180 && -90 < lat2 && lat2 < 90 && -180 < lon2 && lon2 < 180)) {
                cout << "Invalid coordinate(s) entered." << endl;
            } else {
                Vertex<Airport> *depAirport = airportManager.findClosestAirport({lat1, lon1});
                Vertex<Airport> *destAirport = airportManager.findClosestAirport({lat2, lon2});
                cout << "Closest airport for departure is " << depAirport->getInfo().getAirportCode() << endl;
                cout << "Closest airport for arrival is " << destAirport->getInfo().getAirportCode() << endl;
                cout << endl;

                auto paths = script_.getAirportGraph().allShortestPathsWithFilter(depAirport, destAirport, filter);
                airportManager.printPaths(paths, depAirport);
            }
        } break;

    }


    waitEnter();
    return this;
}

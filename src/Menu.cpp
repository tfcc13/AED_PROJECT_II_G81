//
// Created by tiago on 18-12-2023.
//

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
    cout << ">>";
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
            cout << "Sometething test" << endl;
            cout << endl;
            break;
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
            cout << "There are " + to_string(script_.getAirportGraph().getNumVertex()) + " Airports available!" << endl;
            cout << endl;
            break;
        case 2:
            cout << "There are " << script_.getAirlineGraph().getNumVertex() << " Airlines available!" << endl;
            cout << endl;
            break;
        case 3:
            cout << "There are " << script_.getFlightsSet().size() << " Flights available" << endl;
            cout << endl;
            break;

        case 4: {

            cout << "Please write the Airport code" << endl;
            cout << endl;
            input = getInput();

            int flightsCount = airportManager.getAirportFlightsNumber(input);

            if (flightsCount == -1) {
                cout << "That Airport doesn't exist in Airtuga database, try another one please" << endl;
                cout << endl;
                break;
            }

            cout << "There are " << flightsCount << " Flights available" << endl;
            cout << endl;
            break;
        }
        case 5: {
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
                    airportManager.getAirlinesNames(input);
                }
                break;
            }

            break;
    }
        case 6: {
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
    }


    waitEnter();

    return this;
}



//
// Created by tiago on 18-12-2023.
//

#include "Menu.h"

void waitEnter() {
    cout << endl << "Press enter to continue " << endl;
    string tmpString;
    getline(cin,tmpString);
}

string getInput() {
    string input;
    cout << ">>";
    cin >> input;
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

    cout << "\n"

            "    _    ___ ____ _____ _   _  ____    _\n"
            "   / \  |_ _|  _ \_   _| | | |/ ___|  / \ \n"
            "  / _ \  | || |_) || | | | | | |  _  / _ \ \n"
            " / ___ \ | ||  _ < | | | |_| | |_| |/ ___ \ \n"
            "/_/   \_\___|_| \_\|_|  \___/ \____/_/   \_\ \n"
            "\n";

    cout << "MENU: \n\n";

    cout << "(" << ++options << ") >> " << "Go to General Information Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to XXXXX Menu" << endl;
    cout << "(" << ++options << ") >> " << "Go to XXXXX Menu" << endl;
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
            cout << "Sometething test";
            break;
    }

    return invalidOption();
}


GeneralInformationMenu::GeneralInformationMenu(Script &script) : Menu(script) {}

void GeneralInformationMenu::show() {
    cout << CLEAR;
    int options = 0;
    cout << "(" << ++options << ") >> " << "Check how many airpoirts there are" << endl;
    cout << "(" << ++options << ") >> " << "Check how many Airlines there are" << endl;
    cout << "(" << ++options << ") >> " << "Go to XXXXX Menu" << endl;
    cout << "(0) >> Exit "  << endl;
    cout << endl;


}

Menu *GeneralInformationMenu::getNextMenu() {
    int option;

    if(!get(option)) {
        return invalidOption();
    }

    switch (option) {
        case 0:
            return nullptr;
        case 1:
            cout << "Has " << script_.getAirportsMap().size() << "Airports!";
            cout << endl;

        case 2:
            cout << "Sometething test";
            break;
    }

    waitEnter();

    return nullptr;
}



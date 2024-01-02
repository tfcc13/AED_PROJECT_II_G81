#include "Script.h"
#include "Menu.h"

int main(int argc, char* argv[]) {

    string airportsCSV  = "../dataset/airports.csv";
    string airlinesCSV  = "../dataset/airlines.csv";
    string flightsCSV  = "../dataset/flights.csv";

    Script new_script = Script("Dataset");
    new_script.loadDataset(airportsCSV, airlinesCSV, flightsCSV);


    stack<Menu*> menu;

    menu.push(new FirstMenu(new_script));


    while(!menu.empty()) {
        menu.top()->show();
        Menu * menuPtr = menu.top()->getNextMenu();

        if(menuPtr) {
            if(menuPtr != menu.top()) {
                menu.push(menuPtr);
            }
        }
        else {
            delete menu.top();
            menu.pop();
        }
    }

    cout << " THANKS FOR FLYING WITH AIRTUGA" << endl;
    cout << endl;

    return 0;
}



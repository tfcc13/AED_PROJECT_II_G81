//
// Created by tiago on 11-12-2023.
//

#include "Script.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
    Script new_script = Script("Dataset");


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

    return 0;
}



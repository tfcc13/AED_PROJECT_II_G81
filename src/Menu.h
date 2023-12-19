//
// Created by tiago on 18-12-2023.
//

#ifndef PROJECT_II_MENU_H
#define PROJECT_II_MENU_H
#include <iostream>
#include "Script.h"
#include "AirportManager.h"

#define CLEAR "\033[2J\033[1;1H"

class Menu {


protected:
    Script &script_;

    Menu * invalidOption();

public:
    explicit Menu(Script &script);
    virtual ~Menu() = default;

    virtual void show() = 0;

    virtual Menu *getNextMenu() = 0;



};


class FirstMenu : public Menu {
public:
    FirstMenu(Script &script);
    void show() override;
    Menu  *getNextMenu() override;
};

class GeneralInformationMenu : public Menu {
public:
    GeneralInformationMenu(Script &script);
    void show() override;
    Menu * getNextMenu();
};

#endif //PROJECT_II_MENU_H

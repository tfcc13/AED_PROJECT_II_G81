#ifndef PROJECT_II_MENU_H
#define PROJECT_II_MENU_H
#include <iostream>
#include "Script.h"
#include "AirportManager.h"

#define CLEAR "\033[2J\033[1;1H"

class Script;


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

class AirportInformationMenu: public Menu {
public:
    AirportInformationMenu(Script &script);
    void show() override;
    Menu * getNextMenu();
};

class BestFlightMenu : public Menu {
public:
    BestFlightMenu(Script &script);
    void show() override;
    Menu * getNextMenu();
};

class AirportDeparturesMenu : public Menu {
public:
    AirportDeparturesMenu(Script &script);
    void show() override;
    Menu * getNextMenu();
};

class ReachableFromXStops : public Menu {
public:
    ReachableFromXStops(Script &script);
    void show() override;
    Menu * getNextMenu();
};

class AirportArrivalsMenu : public Menu {
public:
    AirportArrivalsMenu(Script &script);
    void show() override;
    Menu * getNextMenu();
};

#endif //PROJECT_II_MENU_H

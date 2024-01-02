#ifndef PROJECT_II_MENU_H
#define PROJECT_II_MENU_H
#include <iostream>
#include "Script.h"
#include "AirportManager.h"

/// Escapa character to clear the terminal screen
#define CLEAR "\033[2J\033[1;1H"

class Script;

class Menu {

protected:
    Script &script_;

    Menu * invalidOption();

public:
    /// Constructor for the menu
    explicit Menu(Script &script);
    /// Destructor for the menu
    virtual ~Menu() = default;

    /// Virtual show function of the menu options
    virtual void show() = 0;

    /// Virtual menu change function
    virtual Menu *getNextMenu() = 0;
};

class FirstMenu : public Menu {
public:
    /// Constructor for the first menu
    FirstMenu(Script &script);

    /// Show the  first menu options
    void show() override;

    /// Change to the next menu
    Menu  *getNextMenu() override;
};

class GeneralInformationMenu : public Menu {
public:
    /// Constructor of the general information menu
    GeneralInformationMenu(Script &script);

    /// Show the general information menu options
    void show() override;
    Menu * getNextMenu();
};

class AirportInformationMenu: public Menu {
public:
    /// Constructor of airport information menu
    AirportInformationMenu(Script &script);

    /// Show the airport information menu options
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

class AirportDeparturesMenu : public Menu {
public:
    /// Constructor of the airport departures menu
    AirportDeparturesMenu(Script &script);

    /// Show the airport departures menu options
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

class ReachableFromXStops : public Menu {
public:
    /// Constructor of the reachable from x stops menu
    ReachableFromXStops(Script &script);

    /// Show the reachable from x stops menu
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

class AirportArrivalsMenu : public Menu {
public:
    /// Constructor of the airport arrivals menu
    AirportArrivalsMenu(Script &script);

    /// Show the airport arrivals menu options
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

class BestFlightMenu : public Menu {
public:
    /// Constructor of the best flight menu
    BestFlightMenu(Script &script);

    /// Show the best flight menu options
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

class BestFlightWithFiltersMenu : public Menu {
public:
    /// Constructor of the best flight with filters menu
    BestFlightWithFiltersMenu(Script &script);

    /// Show the best flight with filters menu options
    void show() override;

    /// Change to the next menu
    Menu * getNextMenu();
};

#endif //PROJECT_II_MENU_H

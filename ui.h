#ifndef UI_H
#define UI_H

#include "domain.h"

//presentation layer

class UI
{
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();

    void init();

private:

    void ListPeople();

    void addPeople();

private:
    Domain domain;
};

#endif // CONSOLEUI_H

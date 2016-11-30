#ifndef UI_H
#define UI_H

#include "domain.h"
#include <vector>
#include "person.h"


//presentation layer

class UI
{
private:
    Domain domain;

    void ListPerson(vector<Person> people, bool search = 0);

    void addPerson();

    void searchPerson();

    void sortPeople();

    void removePerson();
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

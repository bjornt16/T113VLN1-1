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

    //prints out the list, changes is based on how it is printed.
    //function is called from other functions. F.x. from search and the list is printed
    void ListPerson(vector<Person> people, bool search = 0);

    //adds a person to the list
    void addPerson();

    vector<Person> searchPerson();

    //function that sorts
    void sortPeople();

    //function either deletes the whole list or deletes one object from the list
    void removePerson();

    //function that allows the user to modify the list
    void editPerson();
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

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
        //prints out the list, changes is based on how it is printed.
        //function is called from other functions. F.x. from search and the list is printed

    void addPerson();
        //adds a person to the list

    vector<Person> searchPerson();
        //Searches for a function and returns an instant of type Person.

    void sortPeople();
        //function that sorts

    void removePerson();
        //function either deletes the whole list or deletes one object from the list

    void editPerson();


    //function that allows the user to delete everything in the list
    void clearlist();

        //function that allows the user to modify the list

    char validateChar(string prompt, vector<char>);

    string getNameFromUser();
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

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

        //Searches for a function and returns an instant of type Person.
    vector<Person> searchPerson(vector<Person> listToSearch);

        //function that sorts
    void sortPeople();

         //function that allows the user to select one object from the list to delete
    void removePerson();

        //allows the user to edit persons in the list
    void editPerson();

        //function that allows the user to delete the whole list
    void clearlist();

    string capitalizeString(string stringInput);

        //function that allows the user to modify the list

    char validateChar(string prompt, vector<char>);
    string validateString(string prompt, string skipstring = "");
    int validateInt(string prompt);
    vector<int> validateMultipleInt(string prompt);
public:
    UI();

    const string illegal = "Illegal entry, try again!";

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

#ifndef UI_H
#define UI_H

#include "domain.h"
#include "person.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include "ui.h"
#include <vector>

using namespace std;

//presentation layer

class UI
{
private:
    Domain domain;

    //prints out the list, changes is based on how it is printed.
    //function is called from other functions. F.x. from search and the list is printed
    void listPerson(vector<Person> people, bool search = 0);

    //adds a person to the list
    void addPerson();

    //Searches for a function and returns an instant of type Person.
    vector<Person> searchPerson(vector<Person> listToSearch);

    //function that sorts
    vector<Person> sortPerson();

    //function that allows the user to select one object from the list to delete
    void removePerson();

    //allows the user to edit persons in the list
    void editPerson();

    //function that allows the user to delete the whole list
    void clearlist();

    //function that allows the user to change default settings. Ascending or descending.
    void configPerson();

    //function used to capatalize a string
    string capitalizeString(string stringInput);

    //functions that make sure input put into each variable type is correct
    //char validate used when inputing gender(m/f)
    char validateChar(string prompt, vector<char>);

    //string validate used to make first letter in words capital for example names
    string validateString(string prompt, string skipstring = "");

    //int validate used to make sure characters aren't input when asks for int like birth year
    int validateInt(string prompt);
    vector<int> validateMultipleInt(string prompt, size_t maxSize = maxIntToValidate);

    static const size_t maxIntToValidate = 2;
    vector<char> yesOrNo;
    vector<char> acceptedGender;
    const string invalid = "Invalid entry, try again!";

    void projectCredit();
    void numberedOptions(bool includeAge = 0);
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

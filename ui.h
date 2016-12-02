#ifndef UI_H
#define UI_H

#include "domain.h"
#include "person.h"
#include <vector>
#include <iostream>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include "ui.h"
#include <vector>
#include "person.h"

using namespace std;

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
    void sortPerson();

    //function that allows the user to select one object from the list to delete
    void removePerson();

    //allows the user to edit persons in the list
    void editPerson();

    //function that allows the user to delete the whole list
    void clearlist();

    string capitalizeString(string stringInput);

    //function that allows the user to modify the list

    //functions that make sure input put into each variable type is correct
    //char validate used when inputing gender(m/f)
    char validateChar(string prompt, vector<char>);
    //string validate used to make first letter in words capital for example names
    string validateString(string prompt, string skipstring = "");
    //int validate used to make sure characters aren't input when asks for int like birth year
    int validateInt(string prompt);
    vector<int> validateMultipleInt(string prompt, int maxSize = maxIntToValidate);

    static const int maxIntToValidate = 2;
    vector<char> yesOrNo;
    vector<char> acceptedGender;
    const string invalid = "invalid entry, try again!";
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

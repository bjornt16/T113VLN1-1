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
    //declare domain variable, to have access to lower layer.
    Domain domain;

    //listPerson displays the person list passed to it, if search is true, "dummy id's" are shown (used for edit/delete)
    //function is called from other functions. F.x. from search and the list is printed
    void listPerson(vector<Person> people, bool search = 0);

    //function prompts user to input neccasery information about person (name, gender, birthyear, deathyear, nationality)
    //then appends the person to the main person list and peopleFile
    void addPerson();

    //prompts user to search a person list, returns a temporary person list with search results.
    //said search results can be searched again, to further narrow down the search
    vector<Person> searchPerson(vector<Person> listToSearch);

    //prompts user with sort options (by name, age etc) can also search "asc" or "desc"
    //returns sorted person list, based on choices.
    vector<Person> sortPerson();

    //prompts user to search, after search temporary id's are visible, user can further narrow down search or delete person based on the id.
    void removePerson();

    //prompts user to search, after search temporary id's are visible, user can further narrow down search or delete person based on the id.
    void editPerson();

    //function that allows the user to delete the whole list
    //aka drop table / format
    void clearlist();

    //function that allows the user to change default list display settings. Which column to order by, ascending or descending.
    void configPerson();

    //function used to capatalize a string
    string capitalizeString(string stringInput);

    //functions that validates char input, takes string and vector<char> paramters.
    //prompt is the message to prompt user input example: (want to quit (y/n), and the vector is list of acceptable characters.
    //only accepts single character inputs "yes" != 'y'+'e'+'s'..
    //trailing whitespace removed, "y   " = 'y'
    char validateChar(string prompt, vector<char> accepts);

    //function that validates string input, takes string (prompt) parameter and has optional skip paramter, used if input is optional.
    //prompt is the message to prompt user input example: "Enter name: "
    //accepts input like "test    " as "test" .. and "test test  " as one input "test test" (doesn't skip over input from the space)
    string validateString(string prompt, string skipstring = "");

    //function that validates int input, takes in string (prompt) parameter
    //prompt is the message to prompt user input example: "Enter year of birth: "
    //only accepts a single int input, no spaces.
    //example: "15 15" is invalid, "15 " is invalid, "15" is valid.
    int validateInt(string prompt);

    //maxIntToValidate is the max int inputs we'll bother with validating, none of our functions take in 3 ints, so max is set at 2.
    static const size_t maxIntToValidate = 2;

    //function that validates 1+ int inputs, takes in string (prompt) parameter
    //prompt is the message to prompt user input example: "Search from - to"
    //accepts, single and multiple int inputs, based on maxSize parameter, default max = 2
    //trailing white spaces not allowed, example: "15 15 " is invalid, "15 " is invalid, "15 15 15" is invalid, "15 15" is valid, "15" is valid
    vector<int> validateMultipleInt(string prompt, size_t maxSize = maxIntToValidate);

    //vector that holds yes/no characters (n,y), saves us from declaring them multiple times.
    vector<char> yesOrNo;
    //vector that holds gender characters, saves us from declaring them multiple times. (m/f)
    vector<char> acceptedGender;
    //stanardized error message.
    const string invalid = "Invalid entry, try again!";

    //function that displays project credits. (on exit/quit)
    void projectCredit();

    //function that prints the columns from 1-6, used to choose columns easily.
    //saved in a function cause it is reused multiple times, optional parameter if age option should be shown.
    void numberedOptions(bool includeAge = 0);
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

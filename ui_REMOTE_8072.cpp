#include <iostream>
#include <string>
#include "ui.h"
#include "person.h"

using namespace std;

//presentation layer

UI::UI()
{

}

// Should not contain logic for individual commands, that should be in separate functions!
void UI::mainMenu()
{
    cout << "Please enter one of the following commands:" << endl;
    cout << "list - This will list all people in the system" << endl;
    cout << "add - This will add a new person" << endl;
    cout << "delete - Removes an entry" << endl;
    cout << "update - Updates an entry" << endl;
    cout << "search - Searches for given people" << endl;

    string command;
    cin >> command;

    if (command == "list")
    {
        ListPeople();
    }
    else if (command == "add")
    {
        addPeople();
    }
    else if (command == "search")
    {
        // TODO
    }
    else if (command == "delete")
    {

    }
    else if (command == "update"){

    }
    else {
        cout << "Illegal move!" << endl;
    }

}

void UI::ListPeople()
{
    vector<Person> people = domain.getPeople();

    cout << "Displaying persons:" << endl;
    cout << "===============" << endl;
    for (size_t i = 0; i< people.size(); ++i)
    {
        cout << "name: ";
        cout << people[i].getName() << endl;
        cout << "gender: ";
        cout << people[i].getGender() << endl;
        cout << "birth year: ";
        cout << people[i].getBirthYear() << endl;
        cout << "death year: ";
        cout << people[i].getDeathYear() << endl;
        cout << "nationality: ";
        cout << people[i].getNationality() << endl;
        cout << "===============" << endl;
    }
}

void UI::addPeople()
{
    string name;
    int birthYear;
    int deathYear;
    char gender;
    string nationality;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter gender(m/f): ";
    cin >> gender;
    cout << "Enter birth year: ";
    cin >> birthYear;
    cout << "Enter year of death: ";
    cin >> deathYear;
    cout << "Enter nationality: ";
    cin >> nationality;


    Person newPerson(name, gender, birthYear, deathYear, nationality);


    // TODO:
    //service.addPerson(newPerson);
}

void UI::init()
{
    Domain openSaved();

    //openSaved.savedPeople();
}

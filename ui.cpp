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
    string command;

    do
    {
    cout << "Please enter one of the following commands:" << endl;
    cout << "list - This will list all people in the system" << endl;
    cout << "add - This will add a new person" << endl;
    cout << "delete - Removes an entry" << endl;
    cout << "edit - Edit an entry" << endl;
    cout << "search - Searches for given people" << endl;
    cout << "quit - for quit" << endl;
    cin >> command;
<<<<<<< Updated upstream
=======
    }
    while(command != 'q');


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
        search();
    }
    else if (command == "delete")
    {

    }
    else if (command == "edit")
    {

    }
    else {
        cout << "Illegal move!" << endl;
    }
>>>>>>> Stashed changes

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
            search();
        }
        else if (command == "delete")
        {

        }
        else if (command == "edit"){

        }
        else if (command == "quit")
        {
            //þetta á að vera tómt
        }
        else{
            cout << "Illegal move!" << endl;
        }


    } while( !(command == "quit"));
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
    char deadOrAlive;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter gender(m/f): ";
    cin >> gender;
    cout << "Enter nationality: ";
    cin >> nationality;
    cout << "Enter birth year: ";
    cin >> birthYear;
    cout << "Is the the person still alive? Enter y for yes and n for no";
    cin >> deadOrAlive;
    if (deadOrAlive == 'y'){
        Person newPerson(name, gender, birthYear, nationality);
    }
    else if (deadOrAlive == 'n'){
        cout << "Enter death year: ";
        cin >> deathYear;
        Person newPerson(name, gender, birthYear, deathYear, nationality);

    }
    else {
        cout <<"Illegal command, want to enter again? ";
        cin >> deadOrAlive;
    }

    // TODO:
    domain.addPerson(newPerson);
    ListPeople();
}

void UI::search()
{
    string colom;
    string search;
    cout << "what would you like to search by? ";
    cout << "Name, gender, year of birth, year of death or nationality: ";
    cin >> colom;
    if(colom=="Name"||colom=="name")
    {
        cout << "Name: ";
    }
    else if(colom=="Gender"||colom=="gender")
    {
        cout << "Gender: ";
    }
    else if(colom=="Year of birth"||colom=="year of birth")
    {
        cout << "Year of birth: ";
    }
    else if(colom=="Year of death"||colom=="year of death")
    {
        cout << "Year of death: ";
    }
    else if(colom=="Nationality"||colom=="nationality")
    {
        cout << "Nationality: ";
    }
}



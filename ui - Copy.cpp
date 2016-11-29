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
        string name;
        int age;
        cin >> name;
        cin >> age;

        Person newPerson(name);

        // TODO:
        //service.addPerson(newPerson);
    }
    else if (command == "search")
    {
        // TODO
    }
    else
    {

    }

}

void UI::ListPeople()
{
    vector<Person> people = domain.getPeople();

    cout << "Person name:" << endl;
    cout << "===============" << endl;
    for (size_t i = 0; i< people.size(); ++i)
    {
        cout << people[i].getName() << endl;
    }
}


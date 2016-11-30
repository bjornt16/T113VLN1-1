#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "ui.h"
#include <vector>
#include "person.h"


using namespace std;

//presentation layer

UI::UI()
{

}

// Should not contain logic for individual commands, that should be in separate functions!
void UI::mainMenu(bool init)
{
    string command;

    do
    {
        if(!init){
            cout << endl;
        }

        cout << "Please enter one of the following commands:" << endl;
        cout << "list - This will list all people in the system" << endl;
        cout << "add - This will add a new person" << endl;
        cout << "delete - Removes an entry" << endl;
        cout << "edit - Edit an entry" << endl;
        cout << "search - Searches for given people" << endl;
        cout << "quit - for quit" << endl;
        cin >> command;
        cout << endl;

        if (command == "list")
        {
            ListPerson(domain.getPersonList());
        }
        else if (command == "add")
        {
            addPerson();
        }
        else if (command == "search")
        {
            searchPerson();
        }
        else if (command == "delete")
        {
            //todo
            //removePerson();
        }
        else if (command == "edit")
        {
            //todo
            //editPerson();
        }
        else if (command == "quit")
        {
            //þetta á að vera tómt
        }
        else
        {
            cout << "Illegal move! \n" << endl  ;
        }

        init = 0;

    } while( !(command == "quit"));
}

void UI::ListPerson(vector<Person> people, bool search)
{

    cout << "Displaying persons:" << endl;
    cout << "===============" << endl;
    for (size_t i = 0; i< people.size(); ++i)
    {
        if(search){
            cout << "Id: " << i << endl;
        }
        cout << "Name: ";
        cout << people[i].getName() << endl;
        cout << "Gender: ";
        cout << people[i].getGender() << endl;
        cout << "Birth year: ";
        cout << people[i].getBirthYear() << endl;
        cout << "Death year: ";
        people[i].getDeathYear() == 0 ? cout << "-" << endl : cout << people[i].getDeathYear() << endl;
        cout << "Age: ";
        cout << people[i].getAge() << endl;
        cout << "Nationality: ";
        cout << people[i].getNationality() << endl;
        cout << "===============" << endl;
    }
}

void UI::addPerson()
{
    string name, tempName = "";
    int birthYear;
    int deathYear;
    char gender;
    string nationality;

    char c = '\0';

    cout << "Enter name: " << endl;
    while(cin.good()){
        cin.get(c);
        if(c == '\n' && tempName != ""){
            break;
        }
        cin >> tempName;
        name += " " + tempName;
    }
    cout << "Enter gender(m/f): " << endl;
    cin >> gender;
    gender = char(toupper(gender));
    cout << "Enter nationality: " << endl;
    cin >> nationality;
    cout << "Enter birth year: " << endl;
    cin >> birthYear;
    cout << "Enter year of death: ( . to skip)" << endl;
    cin >> deathYear;

    if(cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        deathYear = 0;
    }

    Person newPerson(name, gender, birthYear, deathYear, nationality);
    domain.addPerson(newPerson);

    // TODO:
    ListPerson(domain.getPersonList());
}

void UI::searchPerson()
{
    int column, tempYear = 9999;
    char cSearch;
    string search, tempSearch;
    vector<int> yearSearch;
    bool valid = 1;
    char c = '\0';
    do{
        valid = 1;
        cout << "1 : Name" << endl;
        cout << "2 : Gender" << endl;
        cout << "3 : Year of Birth" << endl;
        cout << "4 : Year of Death " << endl;
        cout << "5 : Nationality" << endl;
        cout << "0 : Cancel" << endl;
        cout << "Select a column to search by: ";
        cin >> column;
        switch(column){

            case 0 : //cancel
            {
                cout << endl;
                break;
            }

            case 1 : //name
            {
                cout << "Name: ";
                while(cin.good()){
                    cin.get(c);
                    if(c == '\n' && tempSearch != ""){
                        break;
                    }
                    cin >> tempSearch;
                    search += " " + tempSearch;
                }
                ListPerson(domain.searchPersonName(search));

                break;
            }
            case 2 : //gender
            {
                cout << "Gender: ";
                cin >> cSearch;
                ListPerson(domain.searchPersonGender(cSearch));
                break;
            }
            case 3 : //birth
            {
                cout << endl << "To search from - to, input two numbers with a space between" << endl;
                cout << "Year of birth: ";

                while(cin.good()){
                    cin.get(c);
                    if(c == '\n' && tempYear != 9999){
                        break;
                    }
                    cin >> tempYear;
                    yearSearch.push_back(tempYear);
                }
                yearSearch.size() > 1 ? ListPerson(domain.searchPersonBirth(yearSearch[0], yearSearch[1])) :
                                        ListPerson(domain.searchPersonBirth(yearSearch[0]));
                break;
            }
            case 4 : //death
            {
                cout << endl << "To search from - to, input two numbers with a space between" << endl;
                cout << "Year of death: ";
                while(cin.good()){
                    cin.get(c);
                    if(c == '\n' && tempYear != 9999){
                        break;
                    }
                    cin >> tempYear;
                    yearSearch.push_back(tempYear);
                }
                yearSearch.size() > 1 ? ListPerson(domain.searchPersonDeath(yearSearch[0], yearSearch[1])) :
                                        ListPerson(domain.searchPersonDeath(yearSearch[0]));
                break;
            }
            case 5 : //nationality
            {
                cout << "Nationality: ";
                cin >> search;
                ListPerson(domain.searchPersonNationality(search));
                break;
            }
            default :{
                cout << "Not a valid choice, try again: ";
                valid = false;
                break;
            }
        }
    }while(!valid);

}

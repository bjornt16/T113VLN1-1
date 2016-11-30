#include <iostream>
#include <iomanip>
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
void UI::mainMenu()
{
    string command;

    do
    {
        cout << "Please enter one of the following commands:" << endl;
        cout << setw(7) << left << "list" << "This will list all people in the system" << endl;
        cout << setw(7) << "add" << "This will add a new person" << endl;
        cout << setw(7) <<"delete" << "Removes an entry" << endl;
        cout << setw(7) <<"edit" << "Edit an entry" << endl;
        cout << setw(7) <<"search" << "Searches for given people" << endl;
        cout << setw(7) <<"sort" << "Sort people in the system" << endl;
        cout << setw(7) <<"quit" <<"For quit" << endl;
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
        else if (command == "sort")
        {
            sortPeople();
        }
        else if (command == "quit")
        {
            //þetta á að vera tómt
        }
        else
        {
            cout << "Illegal move! \n" << endl  ;
        }

        cout << endl;

    } while( !(command == "quit") );
}

void UI::ListPerson(vector<Person> people, bool search)
{

    cout << "Displaying persons:" << endl;
    for (size_t i = 0; i< people.size(); ++i)
    {
        if(search){
            cout << "Id: " << i << endl;

        cout << "Name: ";
        cout << people[i].getName() << endl;
        cout << "Gender: ";
        cout << people[i].getGender() << endl;
        cout << "Birth year: ";
        cout << people[i].getBirthYear() << endl;
        cout << "Death year: ";
        if(people[i].getDeathYear() == 0)
        {
            cout << "-" << endl;
        }
        else
        {
            cout << people[i].getDeathYear() << endl;
        }
        //people[i].getDeathYear() == 0 ? cout << "-" << endl : cout << people[i].getDeathYear() << endl;
        cout << "Age: ";
        cout << people[i].getAge() << endl;
        cout << "Nationality: ";
        cout << people[i].getNationality() << endl;
        }
        cout << "==========================================================================" << endl;
        cout << "Name       Gender      Birth year      Death year      Age     Nationality" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << people[i].getName();
        cout << people[i].getGender();
        cout << people[i].getBirthYear();
        people[i].getDeathYear() == 0 ? cout << "-" << endl: cout << people[i].getDeathYear();
        cout << people[i].getAge();
        cout << people[i].getNationality() << endl;
        cout << "---------------------------------------------------------------------------" << endl;
    }
}

void UI::addPerson()
{
    string name, tempName = "";
    int birthYear;
    int deathYear;
    vector<char> gender;
    char tempChar;
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
    do{
        cout << "Enter gender(M/F): " << endl;

        while(cin.good()){
            if(gender.size() != 0){
                break;
            }
            cin >> tempChar;
            tempChar = char(toupper(tempChar));
            gender.push_back(tempChar);
            if (isdigit(tempChar)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                gender.clear();
                break;
            }
        }

    }
    while (!(gender[0] == 'M' || gender[0] == 'F'));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    cout << "Enter nationality: " << endl;
    cin >> nationality;

    cout << "Enter birth year: " << endl;
    cin >> birthYear;
    while(cin.fail()){
        cout << "Illegal entry, try again" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> birthYear;
    }


    cout << "Enter year of death: ( . to skip)" << endl;
    cin >> deathYear;

    if(cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        deathYear = 0;
    }

    Person newPerson(name, gender[0], birthYear, deathYear, nationality);
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

    cout << "1 : Name" << endl;
    cout << "2 : Gender" << endl;
    cout << "3 : Year of Birth" << endl;
    cout << "4 : Year of Death " << endl;
    cout << "5 : Nationality" << endl;
    cout << "0 : Cancel" << endl;
    cout << "Choose a number between 0-5 to select what column to search in: ";

    do{
        valid = 1;
        cin >> column;

        if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                column = 6;
        }

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
                ListPerson(domain.searchPersonName(search), true);

                break;
            }
            case 2 : //gender
            {
                cout << "Gender: ";
                cin >> cSearch;
                ListPerson(domain.searchPersonGender(cSearch), true);
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
                if (yearSearch.size() > 1)
                {
                    ListPerson(domain.searchPersonBirth(yearSearch[0], yearSearch[1]), true);
                }
                else
                {
                    ListPerson(domain.searchPersonBirth(yearSearch[0]), true);
                }
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
                if(yearSearch.size() > 1)
                {
                    ListPerson(domain.searchPersonDeath(yearSearch[0], yearSearch[1]), true);
                }
                else
                {
                    ListPerson(domain.searchPersonDeath(yearSearch[0]), true);
                }
                break;
            }
            case 5 : //nationality
            {
                cout << "Nationality: ";
                cin >> search;
                ListPerson(domain.searchPersonNationality(search), true);
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

void UI::sortPeople()
{
    bool valid = true;
    do{
        valid = true;
        int column = 0;
        cout << "1 : Name" << endl;
        cout << "2 : Gender" << endl;
        cout << "3 : Year of Birth" << endl;
        cout << "4 : Year of Death " << endl;
        cout << "5 : Nationality" << endl;
        cout << "0 : Cancel" << endl;
        cout << "Select a column to sort by: ";
        cin >> column;
        switch(column)
        {
            case 0 : //cancel
            {
                cout << endl;
                break;
            }

            case 1 : //name sort
            {
                //TODO
                //SortPeopleByName();
                break;
            }

            case 2 :
            {
                //TODO
                //SortPeopleByGender();
                break;
            }

            case 3 :
            {
                //TODO
                //SortPeopleByBY();
                break;
            }

            case 4 :
            {
                //TODO
                //SortPeopleByDY();
                break;
            }

            case 5 :
            {
                //TODO
                //SortPeopleByNat();
                break;
            }
            default :
            {
                cout << "Not a valid choice, try again: ";
                valid = false;
                break;
            }
        }
    } while(valid == false);

}

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
            removePerson();
        }
        else if (command == "edit")
        {
            editPerson();
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
    if(search == true)
    {
        cout << "====";
    }
    cout << "==================================================================================" << endl;
    if(search == true)
    {
        cout << "ID  ";
    }
    cout << "Name                       Gender   Birth year   Death year   Age    Nationality" << endl;
    if(search == true)
    {
        cout << "----";
    }
    cout << "----------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i< people.size(); ++i)
    {
        if(search == true)
        {
            cout << setw(4) << i;
        }
        cout << setw(27) << people[i].getName();
        cout << setw(9) << people[i].getGender();
        cout << setw(13) << people[i].getBirthYear();
        people[i].getDeathYear() == 0 ? cout << setw(13) << "-" : cout << setw(13) << people[i].getDeathYear();
        cout << setw(7) << people[i].getAge();
        cout << setw(13) << people[i].getNationality() << endl;

    }
    if(search == true)
    {
        cout << "====";
    }
    cout << "==================================================================================" << endl;
}

void UI::addPerson()
{
    string name, tempName = "", tempNation = "";
    int birthYear, dYear;
    string deathYear;
    vector<char> gender;
    char tempChar;
    string nationality;
    bool yearFail = 0;

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
        gender.clear();
        tempChar = ' ';
        cout << "Enter gender(M/F): " <<endl;

        while(cin.good()){
            if(gender.size() != 0){
                break;
            }
            cin >> tempChar;
            tempChar = char(toupper(tempChar));
            gender.push_back(tempChar);
            if (isdigit(tempChar) || cin.fail() || !(tempChar == 'M' || tempChar == 'F')) {
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
    while(cin.good()){
        cin.get(c);
        if(c == '\n' && tempNation != ""){
            break;
        }
        cin >> tempNation;
        nationality += " " + tempNation;
    }

    do{
        yearFail = 0;
        cout << "Enter birth year: " << endl;
        cin >> birthYear;
        if(cin.fail()){
            cout << "Illegal entry, try again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            yearFail = 1;
        }
    }while(yearFail);

    do{
        yearFail = 0;
        cout << "Enter year of death: ( . to skip)" << endl;
        cin >> deathYear;
        if((deathYear.find_first_not_of("0123456789") == std::string::npos) || deathYear == "." )
        {
            if(deathYear == ".")
            {
                dYear = 0;
            }
            else
            {
                dYear = stoi( deathYear );
                if(birthYear > dYear)
                {
                    yearFail = 1;
                }
            }
        }
        else{
            yearFail = 1;
        }
    }while(yearFail);

    Person newPerson(name, gender[0], birthYear, dYear, nationality);
    domain.addPerson(newPerson);

    // TODO:
    ListPerson(domain.getPersonList());
}

vector<Person> UI::searchPerson()
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
    vector<Person> listOfFound;

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
                listOfFound = domain.searchPersonName(search);
                ListPerson(listOfFound, true);

                break;
            }
            case 2 : //gender
            {
                cout << "Gender: ";
                cin >> cSearch;
                listOfFound = domain.searchPersonGender(cSearch);
                ListPerson(listOfFound, true);
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
                    listOfFound = domain.searchPersonBirth(yearSearch[0], yearSearch[1]);
                    ListPerson(listOfFound, true);
                }
                else
                {
                    listOfFound = domain.searchPersonBirth(yearSearch[0]);
                    ListPerson(listOfFound, true);
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
                    listOfFound = domain.searchPersonDeath(yearSearch[0], yearSearch[1]);
                    ListPerson(listOfFound, true);
                }
                else
                {
                    listOfFound = domain.searchPersonDeath(yearSearch[0]);
                    ListPerson(listOfFound, true);
                }
                break;
            }
            case 5 : //nationality
            {
                cout << "Nationality: ";
                cin >> search;
                listOfFound = domain.searchPersonNationality(search);
                ListPerson(listOfFound, true);
                break;
            }
            default :{
                cout << "Not a valid choice, try again: ";
                valid = false;
                break;
            }
        }    
    }while(!valid);

    return listOfFound;
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
                ListPerson(domain.sortPeopleByName());
                break;
            }

            case 2 : //gender sort
            {
                //TODO
                ListPerson(domain.sortPeopleByGender());
                break;
            }

            case 3 : //birth year sort
            {
                //TODO
                ListPerson(domain.sortPeopleByBY());
                break;
            }

            case 4 : // death year sort
            {
                //TODO
                ListPerson(domain.sortPeopleByDY());
                break;
            }

            case 5 : // nationality sort
            {
                //TODO
                ListPerson(domain.sortPeopleByNat());
                break;
            }
            default : // loop if incorrect input
            {
                cout << "Not a valid choice, try again: ";
                valid = false;
                break;
            }
        }
    } while(valid == false);

}


void UI::removePerson()
{
    char answer = ' ';
    cout <<"Do you want to remove all of the list? (y/n)" << endl;
    cin >> answer;
    if(answer == 'Y' || answer == 'y'){
        //Todo eyða öllum listanum
    }
    else if (answer =='N' || answer=='n') {
        int idOfPerson;
        cout << "Search for the person you want to delete:" << endl;
        vector<Person> searchResult = searchPerson();
        cout << "Select id of the person you want to delete:" << endl;
        cin >> idOfPerson;
        Person personToRemove = domain.isolatePerson(idOfPerson, searchResult);
        domain.removePerson(personToRemove);
    }
}

void UI::editPerson(){

    char answer;
    int personToEdit = 0;

    cout << "Do you want to edit the list? Y for yes and N for no" << endl;
    cin >> answer;

    if(answer =='Y' || answer == 'y')
    {
        int idOfPerson;
        cout << "Search for the person you want to edit" << endl;
        vector<Person> searchResult = searchPerson();
        cout << "Select id of the person you want to edit" << endl;
        cin >> idOfPerson;
        Person personToEdit = domain.isolatePerson(idOfPerson, searchResult);

    }
     else if (answer =='N' || answer=='n')
    {
        //Það á ekkert að vera hér.
    }

}


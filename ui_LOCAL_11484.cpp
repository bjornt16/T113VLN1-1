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
        cout << setw(7) << left << "list" << "List all entries in the database" << endl;
        cout << setw(7) << "add" << "Add a new entry" << endl;
        cout << setw(7) <<"delete" << "Removes an entry" << endl;
        cout << setw(7) <<"clear" << "Removes all entries" << endl;
        cout << setw(7) <<"edit" << "Edit an entry" << endl;
        cout << setw(7) <<"search" << "Search the database" << endl;
        cout << setw(7) <<"sort" << "Sort the entries" << endl;
        cout << setw(7) <<"quit" <<"To quit" << endl;
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
            //this is meant to be empty
        }
        else if (command == "clear")
        {
            clearlist();
        }
        else
        {
            cout << illegal << endl;
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
    cout << "Name                       Gender   Birth year   Death year   Age    Nationality  " << endl;


    if(search == true)
    {
        cout << "----";
    }
    cout << "----------------------------------------------------------------------------------" << endl;


    for (size_t i = 0; i < people.size(); ++i)
    {
        if(search == true)
        {
            cout << setw(4) << i;
        }
        if(people[i].getName().size() > 27)
        {
            for(int j = 0; j < 24; j++)
            {
                cout << people[i].getName()[j];
            }
            cout << "...";
        }
        else
        {
            cout << setw(27) << people[i].getName();
        }

        cout << setw(9) << people[i].getGender();
        cout << setw(13) << people[i].getBirthYear();
        people[i].getDeathYear() == 0 ? cout << setw(13) << "-" : cout << setw(13) << people[i].getDeathYear();
        cout << setw(7) << people[i].getAge();
        cout << setw(11) << people[i].getNationality() << endl;

    }
    if(search == true)
    {
        cout << "====";
    }
    cout << "==================================================================================" << endl;
}

void UI::addPerson()
{
    string name = "", tempName = "", tempNation = "";
    int birthYear, dYear;
    string deathYear;
    char gender;
    string nationality = "";
    string ignoreLine;
    bool yearFail = 0;

    vector<char> acceptedGender;
    acceptedGender.push_back('M');
    acceptedGender.push_back('F');

    name = validateString("Enter name: ");
    gender = validateChar("Enter Gender (M/F): ", acceptedGender);
    nationality = validateString("Enter nationality: ");
    birthYear = validateInt("Enter year of birth: ");

    do
    {
        yearFail = 0;
        deathYear = validateString("Enter year of death ( . to skip) : ", ".");
        if((deathYear.find_first_not_of("0123456789") == std::string::npos) || deathYear == "" )
        {
            cout << endl << "out"<< endl;
            if(deathYear == "")
            {
                dYear = 0;
            }
            else
            {
                dYear = stoi( deathYear );
                if(birthYear > dYear)
                {
                    yearFail = 1;
                    cout << endl << "Death year must be later than the birth year" << endl;
                }
            }
        }
        else
        {
            yearFail = 1;
            cout << endl << illegal << endl;
            cin.putback('\n');
        }
    }while(yearFail);



    Person newPerson(capitalizeString(name), gender, birthYear, dYear, capitalizeString(nationality));
    domain.addPerson(newPerson);
    ListPerson(domain.getPersonList());
}

vector<Person> UI::searchPerson()
{
    int column;

    char cSearch;
    string sSearch;
    vector<int> iSearch;
    bool valid;
    vector<Person> listOfFound;

    vector<char> acceptedGender;
    acceptedGender.push_back('M');
    acceptedGender.push_back('F');

    do
    {
        valid = 1;
        cout << "1 : Name" << endl;
        cout << "2 : Gender" << endl;
        cout << "3 : Year of Birth" << endl;
        cout << "4 : Year of Death " << endl;
        cout << "5 : Nationality" << endl;
        cout << "0 : Cancel" << endl;
        cout << "Choose a number between 0-5 to select what column to search in: ";
        cin >> column;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            column = 6;
        }

        switch(column)
        {
            case 0 :        //cancel
            {
                cout << endl;
                valid = 1;
                break;
            }

            case 1 :        //name
            {
                sSearch = validateString("Name: ");
                listOfFound = domain.searchPersonName(sSearch);
                break;
            }
            case 2 :        //gender
            {
                cSearch = validateChar("Gender: ",acceptedGender);
                listOfFound = domain.searchPersonGender(cSearch);
                break;
            }
            case 3 :        //birth
            {
                cout << endl << "To search from - to, input two numbers with a space between" << endl;
                iSearch = validateMultipleInt("Year of birth: ");
                if (iSearch.size() > 1)
                {
                    listOfFound = domain.searchPersonBirth(iSearch[0], iSearch[1]);
                }
                else
                {
                    listOfFound = domain.searchPersonBirth(iSearch[0]);
                }
                break;
            }
            case 4 :        //death
            {
                cout << endl << "To search from - to, input two numbers with a space between" << endl;
                iSearch = validateMultipleInt("Year of Death: ");
                if(iSearch.size() > 1)
                {
                    listOfFound = domain.searchPersonDeath(iSearch[0], iSearch[1]);
                }
                else
                {
                    listOfFound = domain.searchPersonDeath(iSearch[0]);
                }
                break;
            }
            case 5 :        //nationality
            {
                sSearch = validateString("Nationality: ");
                listOfFound = domain.searchPersonNationality(sSearch);
                break;
            }
            default :
            {
                cout << illegal;
                valid = 0;
                break;
            }
        }

        if ( (listOfFound.size()) == 0)
        {
            valid = 0;
            cout << "No entry found. Try again:" << endl;
        }

    }while(!valid);

    ListPerson(listOfFound, true);

 /* Væri gaman að gera þetta... þarf bara að breyta öllum serach föllunum þannig að þau taki vextor<Person> inntak. ;D
    char searchAgain;
    cout << "Do you wish to serach within the serch results? (y/n)": ";
    cin >> searchAgain;
    if(searchAgain == 'y' || searchAgain == 'Y')
    {
        listOfFound = searchPerson(listOfFound Person);
    }

  */

    return listOfFound;
}

void UI::sortPeople()
{
    bool valid = true;
    string sortOrder = "asc";
    do{
        valid = true;
        int column = 0;
        if(sortOrder == "asc")
        {
            cout << "1 : Name" << endl;
            cout << "2 : Gender" << endl;
            cout << "3 : Year of Birth" << endl;
            cout << "4 : Year of Death " << endl;
            cout << "5 : Nationality" << endl;
            cout << "9 : to get descending sort" << endl;
            cout << "0 : Cancel" << endl;
            cout << "Select a column to sort by: ";
        }

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
                ListPerson(domain.sortPeopleByName(sortOrder));
                break;
            }

            case 2 : //gender sort
            {
                //TODO
                ListPerson(domain.sortPeopleByGender(sortOrder));
                break;
            }

            case 3 : //birth year sort
            {
                //TODO
                ListPerson(domain.sortPeopleByBY(sortOrder));
                break;
            }

            case 4 : // death year sort
            {
                //TODO
                ListPerson(domain.sortPeopleByDY(sortOrder));
                break;
            }

            case 5 : // nationality sort
            {
                //TODO
                ListPerson(domain.sortPeopleByNat(sortOrder));
                break;
            }
            case 9 : // desc sort
            {
                sortOrder = "desc";
                valid = false;
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
    int idOfPerson;
        cout << "Search for the person you want to delete:" << endl;
        vector<Person> searchResult = searchPerson();
        cout << "Select id of the person you want to delete:" << endl;
        cin >> idOfPerson;
        domain.removePerson(searchResult[idOfPerson]);

}


void UI::editPerson()
{
    int idOfPerson;
    cout << "Search for the person you want to edit" << endl;
    vector<Person> searchResult = searchPerson();
    cout << "Select the ID of the person you want to edit" << endl;
    cin >> idOfPerson;

    Person personToEdit = searchResult[idOfPerson];

    int choiseToEdit;
    cout << "What would you like to edit?" << endl;
    cout << "1 : Name" << endl;
    cout << "2 : Gender" << endl;
    cout << "3 : Year of Birth" << endl;
    cout << "4 : Year of Death " << endl;
    cout << "5 : Nationality" << endl;
    cout << "0 : Cancel" << endl;
    cout << "Please select: " << endl;
    cin >> choiseToEdit;

    bool valid = true;
    do
    {
        switch(choiseToEdit)
        {
            case 0 : //cancel
            {
                cout << endl;
                break;
            }

            case 1 : //Edit name
            {
                string newName = validateString("Please enter the new name:");
                personToEdit.setName(newName);
                break;
            }
            case 2 : //Edit gender
            {
                vector<char> acceptedGender;
                acceptedGender.push_back('M');
                acceptedGender.push_back('F');
                char newGender = validateChar("Please enter a new gender:", acceptedGender);
                personToEdit.setGender(newGender);
                break;
            }

            case 3 : //Edit Year of Birth
            {
                int newYearOfBirth = validateInt("Please enter the new year of birth:");
                personToEdit.setBY(newYearOfBirth);
                break;
            }
            case 4 : //Edit Year of Death
            {
                int newYearOfDeath = validateInt("Please enter the new year of death:");
                personToEdit.setDY(newYearOfDeath);
                break;
            }
            case 5 : //Edit Nationality
            {
                string newNationality = validateString("Please enter the new nationality:");
                personToEdit.setNationality(newNationality);
                break;
            }
            default : // loop if incorrect input
            {
                cout << "Not a valid choice, try again: ";
                valid = false;
                break;
            }
        }
    }while(!valid);

    domain.swapPersons(searchResult[idOfPerson], personToEdit);
}

void UI::clearlist()
{
   char yesOrNo;
   cout << "Are you sure you want to clear the list? (Y/N) : " << endl;
   cin >> yesOrNo;
   yesOrNo = char(tolower(yesOrNo));
   if (yesOrNo == 'y'){

      domain.clearPerson();

   }
   else if (yesOrNo == 'n') {

   }
   else
   {
       cout << "Illegal command!"<< endl;
   }

}

char UI::validateChar(string prompt, vector<char> accepts){

    string tempString;
    char tempChar = ' ', validChar = ' ';
    const size_t maxStringLength = 1;

    do{
        cout << prompt << endl;

        cin >> tempString;
        tempChar = char(toupper(tempString[0]));

        for(size_t i = 0; i < accepts.size(); i++ ){
            if(tempChar == accepts[i] && tempString.size() == maxStringLength){
                validChar = tempChar;
            }
        }

        if (isdigit(tempChar) || validChar == ' ') {
            cout << endl << "Illegal entry, try again" << endl;
        }

    }
    while (validChar == ' ');

    return validChar;

}


string UI::validateString(string prompt, string skipString){
    string tempString, validString;
    char c = '\0';

    cout << prompt << endl;

    while(cin.good()){
        cin.get(c);
        if(c == '\n' && tempString != ""){
            break;
        }
        cin >> tempString;

        if(c != '\n' && c != ' '){
            tempString = c + tempString;
        }

        validString += validString == "" ? tempString : " " + tempString;
    }

    if(validString == skipString){
        validString = "";
    }


    return validString;
}


int UI::validateInt(string prompt){
    int isInt, integer;
    do{
        isInt = 1;
        cout << prompt << endl;
        cin >> integer;
        if(cin.fail()){
            cout << endl << illegal << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isInt = 0;
        }
    }while(!isInt);

    return integer;
}

vector<int> UI::validateMultipleInt(string prompt){

    vector<int> intList;
    int tempInt = 0;
    char c = '\0';


    while(cin.good())
    {
        if(intList.size() == 0){
            cout << prompt << endl;
        }
        cin.get(c);
        if(c == '\n' && intList.size() > 0)
        {
            break;
        }
        cin >> tempInt;
        intList.push_back(tempInt);
        if(cin.fail()){
            cout << endl << illegal << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.putback('\n');
            intList.clear();
        }
    }

    return intList;
}


string UI::capitalizeString(string stringInput)
{
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::tolower);
    stringInput[0] = toupper(stringInput[0]);

    for(size_t i = 0; i < stringInput.size(); i++){
        if(stringInput[i] == ' ' && (i+1) < stringInput.size()){
            stringInput[i+1] = toupper(stringInput[i+1]);
        }
    }

    return stringInput;
}

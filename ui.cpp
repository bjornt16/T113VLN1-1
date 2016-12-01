#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include "ui.h"
#include <vector>
#include "person.h"


using namespace std;

const string illegal = "Illegal entry, try again!";

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
        cout << setw(7) <<"clear" << "Removes all entry" << endl;
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
        else if (command == "clear") {

            clearlist();
        }
        else
        {
            cout << illegal << endl  ;
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
    vector<char> gender;
    char tempChar;
    string nationality = "";
    bool yearFail = 0;

    vector<char> acceptedGender;
    acceptedGender.push_back('M');
    acceptedGender.push_back('F');

    char c = '\0';
    char d = '\0';

    cout << "Enter name: " << endl;
    int NameCounter = 0;
    while(cin.good()){
        cin.get(c);
        if(c == '\n' && tempName != ""){
            break;
        }
        cin >> tempName;
        NameCounter++;
        if(NameCounter == 1)
        {
            name = tempName;
        }
        else
        {
            name += " " + tempName;
        }
    }

    gender = validateChar("Enter Gender (M/F): ", acceptedGender);

    cout << "Enter nationality: " << endl;
    int NatCounter = 0;
    while(cin.good()){
        cin.get(d);
        if(d == '\n' && tempNation != ""){
            break;
        }
        cin >> tempNation;
        NatCounter++;
        if(NatCounter == 1)
        {
            nationality = d + tempNation;
        }
        else
        {
            nationality += " " + tempNation;
        }
    }

    do{
        yearFail = 0;
        cout << "Enter birth year: " << endl;
        cin >> birthYear;
        if(cin.fail()){
            cout << endl << illegal << endl;
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
                    cout << endl << "Death year must be later than the birth year" << endl;

                }
            }
        }
        else{
            yearFail = 1;
             cout << endl << illegal << endl;
        }
    }while(yearFail);

    Person newPerson(name, gender[0], birthYear, dYear, nationality);
    domain.addPerson(newPerson);


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
                cout << illegal;
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
<<<<<<< HEAD
        Person personToRemove = domain.isolatePerson(idOfPerson, searchResult);
        domain.removePerson(personToRemove);

=======
        domain.removePerson(searchResult[idOfPerson]);
    }
    else if (tempAnswer == ' ') {
        cout << "Select number between 0-5" << endl;
    }
>>>>>>> origin/master
}


void UI::editPerson(){

    char tempAnswer;
    //int personToEdit = 0;

    cout << "Do you want to edit the list? Y for yes and N for no" << endl;
    cin >> tempAnswer;
    tempAnswer = char(tolower(tempAnswer));

    if(tempAnswer =='y')
    {
        int idOfPerson;
        cout << "Search for the person you want to edit" << endl;
        vector<Person> searchResult = searchPerson();
        cout << "Select id of the person you want to edit" << endl;
        cin >> idOfPerson;
        Person personToEdit = domain.isolatePerson(idOfPerson, searchResult);
        domain.editPerson(personToEdit);
        UI::addPerson();

    }
     else if (tempAnswer=='n')
    {
        //Það á ekkert að vera hér.
    }
    else {
        cout <<"Illegal command!"<<endl;
    }

}

void UI::clearlist(){

   char yesOrNo;
   cout << "Are you sure you want to clear the list? Y for yes and N for no"<< endl;
   cin >> yesOrNo;
   if (yesOrNo == 'Y' || yesOrNo == 'y'){

      domain.clearPerson();


   }
   else if (yesOrNo == 'N' || yesOrNo == 'n') {

   }
   else
   {
       cout << "Illegal command!"<< endl;
   }

}


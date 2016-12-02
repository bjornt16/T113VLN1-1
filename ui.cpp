#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include "ui.h"
#include <vector>
#include "person.h"

using namespace std;

//presentation layer
UI::UI()
{
    yesOrNo.push_back('Y');
    yesOrNo.push_back('N');
    acceptedGender.push_back('M');
    acceptedGender.push_back('F');
}

// Should not contain logic for individual commands, that should be in separate functions!
void UI::mainMenu()
{
    string command;

    do
    {
        cout << "Please enter one of the following commands:" << endl;
        cout << setw(7) << left << "list" << ": List all entries in the database" << endl;
        cout << setw(7) << "add" << ": Add a new entry" << endl;
        cout << setw(7) << "delete" << ": Removes an entry" << endl;
        cout << setw(7) << "clear" << ": Removes all entries" << endl;
        cout << setw(7) << "edit" << ": Edit an entry" << endl;
        cout << setw(7) << "search" << ": Search the database" << endl;
        cout << setw(7) << "sort" << ": Sort the entries" << endl;
        cout << setw(7) << "config" << ": To change default settings" << endl;
        cout << setw(7) << "quit" << ": To quit" << endl;
        command = validateString("");
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
            searchPerson(domain.getPersonList());
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
            sortPerson();
        }
        else if (command == "quit")
        {
            //this is meant to be empty
        }
        else if (command == "clear")
        {
            clearlist();
        }
        else if(command =="config")
        {
             confiqPerson();
        }
        else
        {
            cout << invalid << endl;
        }
    } while( !(command == "quit") );
}

void UI::ListPerson(vector<Person> people, bool search)
{
    size_t biggestNatSize = 0;

    for(size_t i = 0; i < people.size(); i++)
    {
        if((people[i].getNationality().size()) > biggestNatSize)
        {
            biggestNatSize = people[i].getNationality().size();
        }
    }


    cout << "Displaying persons:" << endl;


    //if function was opened through the search function print this for the id column
    if(search == true)
    {
        cout << "====";
    }
    cout << "==================================================================================";

    //The following if sentences are adding additional "=" marks to the right side of the list depending on how
    //long the strings displayed in the nationality column are
    if(biggestNatSize > 12 && biggestNatSize < 26)
    {
        for(size_t i = 0; i < biggestNatSize-12; i++)
        {
            cout << "=";
        }
        cout << endl;
    }
    else if(biggestNatSize >= 26)
    {
        for(size_t i = 0; i < 26-12; i++)
        {
            cout << "=";
        }
        cout << endl;
    }
    else
    {
        cout << endl;
    }


    //if function was opened through the search function print this for the id column
    if(search == true)
    {
        cout << "ID  ";
    }
    cout << "Name                       Gender   Birth year   Death year   Age    Nationality  " << endl;


    //if function was opened through the search function print this for the id column
    if(search == true)
    {
        cout << "----";
    }
    cout << "----------------------------------------------------------------------------------";

    //The following if sentences are adding additional "=" marks to the right side of the list depending on how
    //long the strings displayed in the nationality column are
    if(biggestNatSize > 12 && biggestNatSize < 26)
    {
        for(size_t i = 0; i < biggestNatSize-12; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    else if(biggestNatSize >= 26)
    {
        for(int i = 0; i < 26-12; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    else
    {
        cout << endl;
    }

    for (size_t i = 0; i < people.size(); ++i)
    {
        //if this function was opened through the search function it will display a Id number for each person
        if(search == true)
        {
            cout << setw(4) << i;
        }
        //if name of person is to long to fit into the name space it will instead print the first
        //24 characters and two dots.
        if(people[i].getName().size() > 27)
        {
            for(int j = 0; j < 24; j++)
            {
                cout << people[i].getName()[j];
            }
            cout << ".. ";
        }
        //else it will print the full name.
        else
        {
            cout << setw(27) << people[i].getName();
        }
        cout << setw(9) << people[i].getGender();
        cout << setw(13) << people[i].getBirthYear();
        people[i].getDeathYear() == 0 ? cout << setw(13) << "-" : cout << setw(13) << people[i].getDeathYear();
        cout << setw(7) << people[i].getAge();

        //if string i for natinality is longer then 26 characters display 23 of them and add a ".. " at the end
        //otherwise print out the whole string
        if(people[i].getNationality().size() > 26)
        {
            for(int j = 0; j < 23; j++)
            {
                cout << people[i].getNationality()[j];
            }
            cout << ".. " << endl;
        }
        else
        {
            cout << setw(biggestNatSize) << people[i].getNationality() << endl;
        }
    }

    //if function was opened through the search function print this for the id column
    if(search == true)
    {
        cout << "====";
    }
    cout << "==================================================================================";


    //The following if sentences are adding additional "=" marks to the right side of the list depending on how
    //long the strings displayed in the nationality column are
    if((biggestNatSize > 12) && (biggestNatSize < 26))
    {
        for(size_t i = 0; i < (biggestNatSize-12); i++)
        {
            cout << "=";
        }
        cout << endl;
    }
    else if(biggestNatSize >= 26)
    {
        for(int i = 0; i < 26-12; i++)
        {
            cout << "=";
        }
        cout << endl;
    }
    else
    {
        cout << endl;
    }
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

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = timePtr->tm_year + 1900;

    //User asked for his information
    name = validateString("Enter name: ");
    gender = validateChar("Enter Gender (M/F): ", acceptedGender);
    nationality = validateString("Enter nationality: ");

    do
    {
        birthYear = validateInt("Enter year of birth: ");
        if(birthYear > currentYear)
        {
            cout << "Birth year must be earlier than current year" << endl;
        }
    }while(birthYear > currentYear);

    do
    {
        yearFail = 0;
        deathYear = validateString("Enter year of death ( . to skip) : ", ".");
        if((deathYear.find_first_not_of("0123456789") == std::string::npos) || deathYear == "" )
        {
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
                else if(dYear > currentYear)
                {
                    yearFail = 1;
                    cout << endl << "Death year can't be higher then current year (" << currentYear << ")" << endl;
                }
            }
        }
        else
        {
            yearFail = 1;
            cout << endl << invalid << endl;
            cin.putback('\n');
        }
    }while(yearFail);


    //adding person to the vector/file
    Person newPerson(capitalizeString(name), gender, birthYear, dYear, capitalizeString(nationality));
    domain.addPerson(newPerson);

    //displaying the list with the person you just added
    ListPerson(domain.getPersonList());
}

vector<Person> UI::searchPerson(vector<Person> listToSearch)
{
    int column;

    char cSearch;
    string sSearch;
    vector<int> iSearch;
    bool valid;
    vector<Person> listOfFound;


    //asks what you want to search by
    do
    {
        valid = 1;
        cout << "1 : Name" << endl;
        cout << "2 : Gender" << endl;
        cout << "3 : Year of Birth" << endl;
        cout << "4 : Year of Death " << endl;
        cout << "5 : Nationality" << endl;
        cout << "6 : Age"<< endl;
        cout << "0 : Cancel" << endl;
        column = validateInt("Choose a number between 0-5 to select what column to search in: ");

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
                listOfFound = domain.searchPersonName(listToSearch,sSearch);
                break;
            }
            case 2 :        //gender
            {
                cSearch = validateChar("Gender (m/f): ",acceptedGender);
                listOfFound = domain.searchPersonGender(listToSearch,cSearch);
                break;
            }
            case 3 :        //birth
            {

                do{
                    cout << endl << "To search from - to, input two numbers with a space between" << endl;
                    iSearch = validateMultipleInt("Year of birth: ");
                    if(iSearch.size() == 2)
                    {
                        listOfFound = domain.searchPersonBirth(listToSearch, iSearch[0], iSearch[1]);
                    }
                    else if(iSearch.size() == 1)
                    {
                        listOfFound = domain.searchPersonBirth(listToSearch, iSearch[0]);
                    }
                }while(!iSearch.size());

                break;
            }
            case 4 :        //death
            {
                do{
                    cout << endl << "To search from - to, input two numbers with a space between" << endl;
                    iSearch = validateMultipleInt("Year of death: ");
                    if(iSearch.size() == 2)
                    {
                        listOfFound = domain.searchPersonDeath(listToSearch, iSearch[0], iSearch[1]);
                    }
                    else if(iSearch.size() == 1)
                    {
                        listOfFound = domain.searchPersonDeath(listToSearch, iSearch[0]);
                    }
                }while(!iSearch.size());
                break;
            }
            case 5 :        //nationality
            {
                sSearch = validateString("Nationality: ");
                listOfFound = domain.searchPersonNationality(listToSearch, sSearch);
                break;
            }
            case 6:         //age
            {
                do{
                    cout << endl << "To search from - to, input two numbers with a space between" << endl;
                    iSearch = validateMultipleInt("Age: ");

                    if(iSearch.size() == 2)
                    {
                        listOfFound = domain.searchPersonAge(listToSearch, iSearch[0], iSearch[1]);
                    }
                    else if(iSearch.size() == 1)
                    {
                        listOfFound = domain.searchPersonAge(listToSearch, iSearch[0]);
                    }
                }while(!iSearch.size());
            break;
            }
            default :
            {
                cout << endl << invalid << endl << endl;
                valid = 0;
                break;
            }
        }

        //nothing was returned from user search
        if ( (listOfFound.size()) == 0 && column != 0)
        {
            valid = 0;
            cout << "No entry found. Try again: " << endl;
        }

    }while(!valid);

    if ( column != 0)
    {
        ListPerson(listOfFound, true);
        do
        {
            valid=1;
            char searchAgain;

            searchAgain = validateChar("Do you wish to search within the search results? (y/n): ",yesOrNo);

            if(searchAgain == yesOrNo[0])
            {
                listOfFound = searchPerson(listOfFound);
            } else if(searchAgain == yesOrNo[1])
            {
                cout << endl;
                break;
            } else
            {
                cout << invalid;
                valid = 0;
            }
        }while(!valid);
    }

    return listOfFound;
}

void UI::sortPerson()
{
    bool valid = 1;
    string sortOrder = "asc";
    const int failState = 99;
    int column;
    string choice = "";

    //asks what you want to sort by
    cout << "1 : Name" << endl;
    cout << "2 : Gender" << endl;
    cout << "3 : Year of Birth" << endl;
    cout << "4 : Year of Death " << endl;
    cout << "5 : Nationality" << endl;
    cout << "6 : Age" << endl;
    cout << "0 : Cancel" << endl;

    //option to sort descendingly
    do{
        valid = 1;
        cout << endl << "To sort in descending order (# desc)";

        choice = validateString("Select a column to sort by: ");
        if(isdigit(choice[0]))
        {
            column = stoi(choice.substr(0));
            sortOrder = choice.size() > 1 ? choice.substr(choice.find(' ')+1) : "asc";
            if(sortOrder != "asc" && sortOrder != "desc")
            {
                column = failState;
                sortOrder = "asc";
                cin.putback('\n');
            }
        }

        switch(column)
        {
            //calls a different function depending on number selected
            case 0 : //cancel
            {
                cout << endl;
                break;
            }

            case 1 : //name sort
            {
                ListPerson(domain.sortPeopleByName(sortOrder));
                break;
            }

            case 2 : //gender sort
            {
                ListPerson(domain.sortPeopleByGender(sortOrder));
                break;
            }

            case 3 : //birth year sort
            {
                ListPerson(domain.sortPeopleByBY(sortOrder));
                break;
            }

            case 4 : // death year sort
            {
                ListPerson(domain.sortPeopleByDY(sortOrder));
                break;
            }

            case 5 : // nationality sort
            {
                ListPerson(domain.sortPeopleByNat(sortOrder));
                break;
            }
            case 6 :
            {
                ListPerson(domain.sortPeopleByAge(sortOrder));
                break;
            }
            case failState:
            default : // loop if incorrect input
            {
                cout << endl << invalid << endl;
                valid = 0;
                break;
            }
        }
    } while(!valid);
    cout << endl;
}

void UI::removePerson()
{
    int idOfPerson;
    cout << "Search for the person you want to delete:" << endl;
    vector<Person> searchResult = searchPerson(domain.getPersonList());
    if(searchResult.size())
    {
        idOfPerson = validateInt("Select id of the person you want to delete: ");
        domain.removePerson(searchResult[idOfPerson]);
    }
}

void UI::editPerson()
{
    int idOfPerson;
    cout << "To find the person you wish to edit. Please select a column to search by: " << endl;
    vector<Person> searchResult = searchPerson(domain.getPersonList());
    if(searchResult.size())
    {
        idOfPerson = validateInt("Select id of the person you want to edit: ");


        //finding the person you want to edit
        Person personToEdit = searchResult[idOfPerson];

        //selecting what you want to edit about the person
        int choiseToEdit;
        cout << "1 : Name" << endl;
        cout << "2 : Gender" << endl;
        cout << "3 : Year of Birth" << endl;
        cout << "4 : Year of Death " << endl;
        cout << "5 : Nationality" << endl;
        cout << "0 : Cancel" << endl;

        choiseToEdit = validateInt("Please select what you would like to edit: ");

        bool valid = true;
        do
        {
            //calls function based on what you wanted to edit
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
                    char newGender = validateChar("Please enter a new gender: ", acceptedGender);
                    personToEdit.setGender(newGender);
                    break;
                }
                case 3 : //Edit Year of Birth
                {
                    int newYearOfBirth = validateInt("Please enter the new year of birth: ");
                    personToEdit.setBY(newYearOfBirth);
                    break;
                }
                case 4 : //Edit Year of Death
                {
                    int newYearOfDeath = validateInt("Please enter the new year of death: ");
                    personToEdit.setDY(newYearOfDeath);
                    break;
                }
                case 5 : //Edit Nationality
                {
                    string newNationality = validateString("Please enter the new nationality: ");
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
        }
        while(!valid);
        domain.swapPersons(searchResult[idOfPerson], personToEdit);
    }
}

void UI::clearlist()
{
    //self explainatory
   char choice;
   choice = validateChar("Are you sure you want to clear the list? (y/n) : ", yesOrNo);
   if (choice == yesOrNo[0])
   {
      domain.clearPerson();
   }
}

char UI::validateChar(string prompt, vector<char> accepts){

    string tempString = "";
    char validChar = ' ';
    const size_t maxStringLength = 1;

    //function used to validate that the character you input is in the accepts vector
    do
    {
    tempString = validateString(prompt);

        tempString[0] = toupper(tempString[0]);

        for(size_t i = 0; i < accepts.size(); i++ )
        {
            if(tempString[0] == accepts[i] && tempString.size() == maxStringLength)
            {
                validChar = tempString[0];
            }
        }
        if(validChar == ' ')
        {
            cout << endl << invalid << endl;
        }

    }while(validChar == ' ');

    return validChar;
}

string UI::validateString(string prompt, string skipString){
    string validString = "";

    //combines a multiple input strings into one, for example first and second names
    cout << endl << prompt << endl;
    do
    {
        getline(cin, validString);
        validString.resize(validString.find_last_not_of(" ")+1);
    }while(validString.size() == 0);

    if(validString == skipString)
    {
        validString = "";
    }
    return validString;
}

int UI::validateInt(string prompt)
{
    vector<int> intList;

    //makes sure letters are not input when user is asked for intigers
    do
    {
        intList = validateMultipleInt(prompt, 1);
    }while(intList.size() != 1);

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return intList[0];
}

vector<int> UI::validateMultipleInt(string prompt, size_t maxSize)
{
    vector<int> intList;
    int tempInt = 0;
    char c = '\0';
    size_t counter = 0;

    while(cin.good())
    {
        if(intList.size() == 0)
        {
            cout << endl << prompt << endl;
        }
        else
        {
            counter++;
            cin.get(c);
            if(c == '\n' && counter == maxSize)
            {

            }
            else if(c == '\n')
            {
                cin.putback('\n');
                break;
            }
            else if(c == ' ' && counter == maxSize)
            {
                intList.clear();
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.putback('\n');
            }
        }
        if(counter < maxSize)
        {
            cin >> tempInt;
            intList.push_back(tempInt);
        }
        else if(maxSize > intList.size())
        {
            cout << endl << invalid << endl;
            break;
        }
        else
        {
            cin.putback('\n');
        }
        if(cin.fail())
        {
            cout << endl << invalid << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            intList.clear();
            counter = 0;
        }
    }
    return intList;
}

string UI::capitalizeString(string stringInput)
{
    //strings which have been run through validate string function have their first character
    //in each word capitalized
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::tolower);
    stringInput[0] = toupper(stringInput[0]);

    for(size_t i = 0; i < stringInput.size(); i++)
    {
        if(stringInput[i] == ' ' && (i+1) < stringInput.size())
        {
            stringInput[i+1] = toupper(stringInput[i+1]);
        }
    }
    return stringInput;
}

void UI::confiqPerson()
{
    bool valid = 1;
    int changeSettings;

    cout << "1 : cancel" << endl;
    cout << "2 : sort order" << endl;
    cout << "3 : default sort" << endl;

        do
        {
        valid = 1;
        changeSettings = validateInt("Choose a number between 1-3 to select what column to change settings: ");

        switch(changeSettings)
        {
            case 1: //cancel
            {
                valid = 1;
                cout << endl;
                break;
            }
            case 2 : //sort Order
            {


                break;
            }
            case 3 : //Choose default sort
            {

                break;
            }
            default : // loop if incorrect input
            {
                cout << "Not a valid choice, try again: ";
                valid = 0;
                break;
            }
        }
        }while(!valid);
}

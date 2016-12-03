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
UI::UI() //ui default constructor, puts accepted yes/no and m/f vales into their appropriate vectors
{
    yesOrNo.push_back('Y');
    yesOrNo.push_back('N');
    acceptedGender.push_back('M');
    acceptedGender.push_back('F');
}

void UI::mainMenu()
{
    string command;
    bool valid = 1;

    do
    {
        //lists the main menu, if the last input was valid
        if(valid)
        {
            cout << setw(7) << left << "list" << ": List all entries in the database" << endl;
            cout << setw(7) << "add" << ": Add a new entry" << endl;
            cout << setw(7) << "delete" << ": Removes an entry" << endl;
            cout << setw(7) << "clear" << ": Removes all entries" << endl;
            cout << setw(7) << "edit" << ": Edit an entry" << endl;
            cout << setw(7) << "search" << ": Search the database" << endl;
            cout << setw(7) << "sort" << ": Sort the entries" << endl;
            cout << setw(7) << "config" << ": To change sort settings" << endl;
            cout << setw(7) << "quit" << ": To quit" << endl;
        }
        command = validateString("Please enter one of the commands: ");
        cout << endl;
        valid = 1;

        if (command == "list")
        {
            listPerson(domain.sortPersonByDefault(domain.getPersonList()));
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
            listPerson(sortPerson(domain.getPersonList()));
        }
        else if (command == "quit")
        {
           projectCredit();
        }
        else if (command == "clear")
        {
            clearList();
        }
        else if(command =="config")
        {
             configPerson();
        }
        else
        {
            cout << invalid << endl;
            valid = 0;
        }
    } while( !(command == "quit") );
}

//our "print" function, takes in a person list parameter, and prints them in the order the list is in.
//displays dummy id's used in edit/delete if the print/list was a part of a search
void UI::listPerson(vector<Person> people, bool search)
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

    //if function was opened through the search function print this for the ID column
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


    //if function was opened through the search function print this for the ID column
    if(search == true)
    {
        cout << "ID  ";
    }
    cout << "Name                       Gender   Birth year   Death year   Age    Nationality  " << endl;


    //if function was opened through the search function print this for the ID column
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
        //if this function was opened through the search function it will display a ID number for each person
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
    
    //if function was opened through the search function print this for the ID column
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

//function prompts user to input neccasery information about person (name, gender, birthyear, deathyear, nationality)
//then appends the person to the main person list and peopleFile
void UI::addPerson()
{
    string name = "", tempName = "", tempNation = "";
    int birthYear = 0, dYear = 0;
    string deathYear = "";
    char gender = ' ';
    string nationality = "";
    bool yearFail = 0;

    //get the current year
    const int timeBias = 1900;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = timePtr->tm_year + timeBias;

    //User asked for person information
    cout << endl;
    name = validateString("Enter name: ");
    gender = validateChar("Enter Gender (M/F): ", acceptedGender);
    nationality = validateString("Enter nationality: ");

    //birthyear cannot be set to a future year
    do
    {
        birthYear = validateInt("Enter year of birth: ");
        if(birthYear > currentYear)
        {
            cout << "Birth year must be earlier than current year" << endl;
        }
    }while(birthYear > currentYear);

    //deathyear is skippable, with "." which defaults to 0.
    //loops until deathyear is valid, i.e. either "." or an actual number,
    //the number cannot be lower than birthyear, and cannot be higher than currentyear
    do
    {
        yearFail = 0;
        deathYear = validateString("Enter year of death ( . to skip) : ", ".");
        if((deathYear.find_first_not_of("0123456789") == std::string::npos) || deathYear == "" )
        {
            if(deathYear == "")
            {
                //in our system, a deathyear of 0 is the same as "not dead" (my kingdom for a null!)
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
    }while(yearFail); //loop until year is valid


    //adding person to the vector/file
    Person newPerson(capitalizeString(name), gender, birthYear, dYear, capitalizeString(nationality));
    domain.addPerson(newPerson);

    //displaying the list with the person you just added
    listPerson(domain.getPersonList());
}

//prompts user to search a person list, returns a temporary person list with search results.
//said search results can be searched again, to further narrow down the search
vector<Person> UI::searchPerson(vector<Person> listToSearch)
{
    int column = 0;
    char cSearch = ' ';
    string sSearch = "";
    vector<int> iSearch;
    bool valid = 1;
    vector<Person> listOfFound;

    int const searchA = 1;
    int const searchS = 2;
    int const sortS = 3;
    int const mM = 0;



    //asks what you want to search by
    do
    {
        valid = 1;
        numberedOptions(1);
        column = validateInt("Select a column to search by: ");

        switch(column)
        {
            case cancel :        //cancel
            {
                cout << endl;
                valid = 1;
                break;
            }

            case nameColumn :        //name
            {
                sSearch = validateString("Name: ");
                listOfFound = domain.searchPersonName(listToSearch,sSearch);
                break;
            }
            case genderColumn :        //gender
            {
                cSearch = validateChar("Gender (m/f): ",acceptedGender);
                listOfFound = domain.searchPersonGender(listToSearch,cSearch);
                break;
            }
            case birthColumn :        //birth
            {

                do{
                    cout << endl << "Search year, or from year to later year:  '1995' or '1995 2005' " << endl;
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
            case deathColumn :        //death
            {
                do{
                    cout << endl << "Search year, or from year to later year:  '1995' or '1995 2005' " << endl;
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
            case natColumn :        //nationality
            {
                sSearch = validateString("Nationality: ");
                listOfFound = domain.searchPersonNationality(listToSearch, sSearch);
                break;
            }
            case ageColumn:         //age
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
        listPerson(domain.sortPersonByDefault(listOfFound), true);
        do
        {
            valid=1;
            int searchAgain;

            cout << "1 : Search Again " << endl;
            cout << "2 : Search within search result" << endl;
            cout << "3 : Sort search result" << endl;
            cout << "0 : Continue" << endl;

            searchAgain = validateInt("What would you like to do now: ");

            switch(searchAgain)
            {
                case searchA:
                {
                    listOfFound = searchPerson(domain.getPersonList());
                    break;
                }
                case searchS:
                {
                    listOfFound = searchPerson(listOfFound);
                    break;
                }
                case sortS:
                {
                    listOfFound = sortPerson(listOfFound);
                    listPerson(listOfFound);
                    valid = 0;
                    break;
                }
                case mM:
                {
                    cout << endl;
                    break;
                }
                default:
                {
                    cout << invalid;
                    valid = 0;
                }
            }

        }while(!valid);
    }
    return listOfFound;
}

//prompts user with sort options (by name, age etc) can also search "asc" or "desc"
//returns sorted person list, based on choices.
vector<Person> UI::sortPerson(vector<Person> personList, int sortColumn)
{
    Config config = domain.getConfig();
    vector<Person> sortedList;
    bool valid = 1;
    string sortOrder = config.SortOrder; //default is saved sortOrder
    string choice = "";

    //asks what you want to sort by
    cout << endl;
    numberedOptions(1);


    //option to sort descendingly
    do{
        valid = 1;
        if(sortColumn == dummyNull)
        {
            cout << endl << "Choose sort order by adding 'asc' or 'desc', example: (1 desc)";

            //asks what you want to sort by
            choice = validateString("Select a column to sort by: ");

            //get digit from string, and order if available, else use saved sortOrder
            //accepted inputs "#", "# desc", "# asc" .. # being the column number
            if(isdigit(choice[0]))
            {
                sortColumn = stoi(choice.substr(0));

                if(choice.size() > 1 )
                {
                    sortOrder = choice.substr(choice.find(' ')+1);
                }

                if(sortOrder != "asc" && sortOrder != "desc")
                {
                    sortColumn = dummyNull;
                    cin.putback('\n');
                }
            }
        }


        switch(sortColumn)
        {
            //calls a different function depending on number selected
            case cancel : //cancel
            {
                cout << endl;
                break;
            }

            case nameColumn : //name sort
            {
                sortedList = domain.sortPersonByName(sortOrder,personList);
                break;
            }

            case genderColumn : //gender sort
            {
                sortedList = domain.sortPersonByGender(sortOrder,personList);
                break;
            }

            case birthColumn : //birth year sort
            {
                sortedList = domain.sortPersonByBY(sortOrder,personList);
                break;
            }

            case deathColumn : // death year sort
            {
                sortedList = domain.sortPersonByDY(sortOrder,personList);
                break;
            }

            case natColumn : // nationality sort
            {
                sortedList = domain.sortPersonByNat(sortOrder,personList);
                break;
            }
            case ageColumn :
            {
                sortedList = domain.sortPersonByAge(sortOrder,personList);
                break;
            }
            case dummyNull:
            default : // loop if incorrect input
            {
                cout << endl << invalid << endl;
                valid = 0;
                break;
            }
        }
    } while(!valid);
    cout << endl;

    return sortedList;
}

//prompts user to search, after search temporary id's are visible, user can further narrow down search or delete person based on the id.
void UI::removePerson()
{
    int idOfPerson = 0;
    cout << endl << "Search for the person you wish to delete:" << endl;
    vector<Person> searchResult = searchPerson(domain.getPersonList());
    if(searchResult.size())
    {
        idOfPerson = validateInt("Select ID of the person you want to delete: ");
        domain.removePerson(searchResult[idOfPerson]);
    }
}

//prompts user to search, after search temporary id's are visible, user can further narrow down search or delete person based on the id.
void UI::editPerson()
{
    int idOfPerson = 0;
    cout << endl << "Search for the person you wish to edit: " << endl;
    vector<Person> searchResult = searchPerson(domain.getPersonList());
    if(searchResult.size())
    {
        idOfPerson = validateInt("Select ID of the person you want to edit: ");


        //finding the person you want to edit
        Person personToEdit = searchResult[idOfPerson];

        //selecting what you want to edit about the person
        int choiseToEdit;
        numberedOptions();
        choiseToEdit = validateInt("Please select what you would like to edit: ");

        bool valid = true;
        do
        {
            //calls function based on what you wanted to edit
            switch(choiseToEdit)
            {
                case cancel : //cancel
                {
                    cout << endl;
                    break;
                }
                case nameColumn : //Edit name
                {
                    string newName = validateString("Please enter the new name:");
                    personToEdit.setName(newName);
                    break;
                }
                case genderColumn : //Edit gender
                {
                    char newGender = validateChar("Please enter a new gender:", acceptedGender);
                    personToEdit.setGender(newGender);
                    break;
                }
                case birthColumn : //Edit Year of Birth
                {
                    int newYearOfBirth = validateInt("Please enter the new year of birth: ");
                    personToEdit.setBY(newYearOfBirth);
                    break;
                }
                case deathColumn : //Edit Year of Death
                {
                    int newYearOfDeath = validateInt("Please enter the new year of death: ");
                    personToEdit.setDY(newYearOfDeath);
                    break;
                }
                case natColumn : //Edit Nationality
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
        domain.swapPerson(searchResult[idOfPerson], personToEdit);
    }
}

//function that allows the user to delete the whole list
//aka drop table / format
void UI::clearList()
{
   char choice;
   choice = validateChar("Are you sure you want to clear the list? (y/n) : ", yesOrNo);
   if (choice == yesOrNo[0])
   {
      domain.clearPerson();
   }
}

//functions that validates char input, takes string and vector<char> paramters.
//prompt is the message to prompt user input example: (want to quit (y/n), and the vector is list of acceptable characters.
//only accepts single character inputs "yes" != 'y'+'e'+'s'..
//trailing whitespace removed, "y   " = 'y'
char UI::validateChar(string prompt, vector<char> accepts)
{

    string tempString = "";
    char validChar = ' ';
    const size_t maxStringLength = 1;

    //function used to validate that the character you input is in the accepts vector
    do
    {
    tempString = validateString(prompt);

        //toupper to reduce comparisons checks
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

//function that validates string input, takes string (prompt) parameter and has optional skip paramter, used if input is optional.
//prompt is the message to prompt user input example: "Enter name: "
//accepts input like "test    " as "test" .. and "test test  " as one input "test test" (doesn't skip over input from the space)
string UI::validateString(string prompt, string skipString)
{
    string validString = "";

    //combines a multiple input strings into one, for example first and second names
    cout << prompt << endl;
    //get the entire input, cut of trailing whitespace
    do
    {
        getline(cin, validString);
        validString.resize(validString.find_last_not_of(" ")+1);
    }while(validString.size() == 0);

    //if input is the same as the skipString, reset string
    if(validString == skipString)
    {
        validString = "";
    }
    return validString;
}

//function that validates int input, takes in string (prompt) parameter
//prompt is the message to prompt user input example: "Enter year of birth: "
//only accepts a single int input, no spaces.
//example: "15 15" is invalid, "15 " is invalid, "15" is valid.
int UI::validateInt(string prompt)
{
    vector<int> intList;

    //makes sure input is a digit, avoids endless loop from entering a charater as int
    do
    {
        intList = validateMultipleInt(prompt, 1);
    }while(intList.size() != 1);

    //reset input buffer, just incase
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return intList[0];
}

//function that validates 1+ int inputs, takes in string (prompt) parameter
//prompt is the message to prompt user input example: "Search from - to"
//accepts, single and multiple int inputs, based on maxSize parameter, default max = 2
//trailing white spaces not allowed, example: "15 15 " is invalid, "15 " is invalid, "15 15 15" is invalid, "15 15" is valid, "15" is valid
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
            cout << prompt << endl;
        }
        else
        {
            counter++;
            cin.get(c);
            if(c == '\n' && counter == maxSize)
            {
                //empty if, used to avoid lower else if, state is still valid at this point
            }
            else if(c == '\n')
            {
                cin.putback('\n'); //avoids the input stalling, as it waits for another input.
                break;
            }
            else if(c == ' ' && counter == maxSize)
            {
                //if input ends on whitespace, it is deemed invalid, clear the intList and clean up input buffer.
                intList.clear();
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.putback('\n');
            }
        }
        //put int into the int list if number int inputs is less than maxSize
        if(counter < maxSize)
        {
            cin >> tempInt;
            intList.push_back(tempInt);
        }
        else if(maxSize > intList.size()) //if number of int inputs exceeds max, it's deemed invalid
        {
            cout << endl << invalid << endl;
            break;
        }
        else
        {
            cin.putback('\n'); //avoids the input stalling, as it waits for another input.
        }
        if(cin.fail())
        {
            //if input fails .. i.e. if input is a char/string, clean up list, and input buffer.
            //this is ofcourse also an invalid input
            cout << endl << invalid << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            intList.clear();
            counter = 0;
        }
    }
    return intList;
}

//function used to capatalize a string
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

//function that allows the user to change default list display settings. Which column to order by, ascending or descending.
void UI::configPerson()
{
    bool valid = 1;
    int changeSettings = 0;
    int setting = 0;
    string sortOrder;
    Config newConfig = domain.getConfig();
    const int ascending = 1;
    const int descending = 2;

    const int sortOrderNum = 1;
    const int sortColumnNum = 2;

    cout << "1 : Set default sort order" << endl;
    cout << "2 : Set default sort column" << endl;
    cout << "0 : cancel" << endl;

        do
        {
        valid = 1;
        changeSettings = validateInt("Choose a number between 0-2 to select what column to change settings: ");
        cout << endl;

        switch(changeSettings)
        {
            case cancel: //cancel
            {
                valid = 1;
                cout << endl;
                break;
            }
            case sortOrderNum : //sort Order
            {
                cout << "1 : Ascending" << endl;
                cout << "2 : Descending" << endl;
                cout << "0 : Cancel" << endl;
                setting = validateInt("Choose a number between 0-2 to change default sort order: ");
                cout << endl;
                if(setting == cancel)
                {
                    break;
                }
                else if(setting == ascending)
                {
                    sortOrder = "asc";
                }else if(setting == descending)
                {
                    sortOrder = "desc";
                }
                //override old config
                newConfig.SortOrder = sortOrder;
                domain.setConfig(newConfig);
                break;
            }
            case sortColumnNum : //Choose default sort
            {
                numberedOptions(1);
                setting = validateInt("Choose a number between 0-6 to change default sort column: ");
                cout << endl;
                //override old config
                newConfig.sortColumn = setting;
                domain.setConfig(newConfig);
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

//function that prints the columns from 1-6, used to choose columns easily.
//saved in a function cause it is reused multiple times, optional parameter if age option should be shown.
void UI::numberedOptions(bool includeAge)
{
    cout << "1 : Name" << endl;
    cout << "2 : Gender" << endl;
    cout << "3 : Year of Birth" << endl;
    cout << "4 : Year of Death " << endl;
    cout << "5 : Nationality" << endl;
    if(includeAge)
    {
        cout << "6 : Age" << endl;
    }
    cout << "0 : Cancel" << endl;
}

//function that displays project credits. (on exit/quit)
void UI::projectCredit()
{
    cout << "    _______  _______  _______  __   __       _____         " << endl
         << "   |       ||       ||   _   ||  |_|  |     |  _  |        " << endl
         << "   |_     _||    ___||  |_|  ||       |     | |_| |        " << endl
         << "     |   |  |   |___ |       ||       |    |   _   |       " << endl
         << "     |   |  |    ___||       ||       |    |  | |  |       " << endl
         << "     |   |  |   |___ |   _   || ||_|| |    |  |_|  |       " << endl
         << "     |___|  |_______||__| |__||_|   |_|    |_______|       " << endl
         << "   _______  ______    _______  ______   ___  _______       " << endl
         << "  |    ___||    _ |  |       ||      | |   ||       | __   " << endl
         << "  |   |    |   | ||  |    ___||  _    ||   ||_     _||__|  " << endl
         << "  |   |    |   |_||_ |   |___ | | |   ||   |  |   |   __   " << endl
         << "  |   |    |    __  ||    ___|| |_|   ||   |  |   |  |__|  " << endl
         << "  |   |___ |   |  | ||   |___ |       ||   |  |   |        " << endl
         << "  |_______||___|  |_||_______||______| |___|  |___|        " << endl << endl;

    cout << "           -Anna Kristin Halldorsdottir" << endl;
    cout << "           -Bjorn Thorsson" << endl;
    cout << "           -Fridrik Snaer Tomasson" << endl;
    cout << "  ()_()    -Isak Gretarson" << endl;
    cout << "  (*.*)    -Margret Finnbogadottir" << endl;
    cout << " c(\")(\")   -Solveig Sara Samuelsdottir" << endl;
    cout << endl;
}

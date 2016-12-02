#include "data.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "person.h"
#include "config.h"

using namespace std;
//data layer

Data::Data()
{
    readPeopleFromFile();
    readConfigFromFile();
}

//getList returns copy of the list (vector) containing all persons in the "database"
vector<Person> Data::getList()
{
    return list;
}

//writePersonToFile writes new person to file and adds person to the main vector containing all persons.
void Data::writePersonToFile(Person p)
{
    //open and append to file
    ofstream file;
    file.open(peopleFile, ios::out | ios::app);

    //writeSinglePersonToOpenFile takes person and file as parameter, adds that person, to that file.
    writeSinglePersonToOpenFile(p, file);

    //add person to person list
    list.push_back(p);

    file.close();
}

//readPeopleFromFile reads current peopleFile entries into main list.
//done at start up
void Data::readPeopleFromFile()
{
    //clear list first, just in case.
    list.clear();

    ifstream file;
    file.open(peopleFile);
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof(); //check if file is Empty

    //declare variables to be filled
    string name = "", nationality = "";
    char gender = ' ';
    int bYear = 0, dYear = 0;

    while(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty ) //lots of checks, to make sure file contains data/exists
    {

        file >> name >> gender >> bYear >> dYear >> nationality;

        //multi word strings have underscores instead of whitespace
        //this replaces them with white spaces
        replace( name.begin(), name.end(), '_', ' ');
        replace( nationality.begin(), nationality.end(), '_', ' ');

        //declare newPerson, then add it to the person list. (vector)
        Person newPerson(name, gender, bYear, dYear, nationality);
        list.push_back(newPerson);
    }  
    file.close();
}

//getConfig returns a copy of the config object
Config Data::getConfig(){
    return config;
}

//writeConfigToFile takes in Config class as parameter, and writes the config settings to the config.txt file
void Data::writeConfigToFile(Config c)
{
    //open and write in file
    ofstream file;
    file.open(configFile);

    file << "\n" << c.sortColumn << " " << c.SortOrder;

    //overwrites config object with new settings.
    config.sortColumn = c.sortColumn;
    config.SortOrder = c.SortOrder;

    file.close();
}

//readConfigFromFile reads current config entries into main config object.
//done at start up
void Data::readConfigFromFile(){

    ifstream file;
    file.open(configFile);
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof(); //checks if file is empty

    string sortOrder = "";
    int sortColumn = 0;

    if(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty ) //check if file, exists, is open and is generally usable
    {
        file >> sortColumn >> sortOrder;

        //overrwite main config object.
        config.sortColumn = sortColumn;
        config.SortOrder = sortOrder;

    }

    file.close();
}


//removePersonFromDatabase takes person class as parameter, checks if it exists in the main person List, and removes person from both file and list.
void Data::removePersonFromDatabase(Person personToRemove)
{
    //make changes to the vector holding people
    int vectorSize = list.size();
    for(int i=0; i < vectorSize; i++)
    {
        if(list[i] == personToRemove)
        {
            //if found, remove person from list and file
            list.erase(list.begin()+i);
            rewriteDataFile();
            break;
        }
    }
}

//overwrites peopleFile with current person List.
void Data::rewriteDataFile()
{
    //first delete current peopleFile
    remove(peopleFile.c_str());

    ofstream file;
    file.open(peopleFile, ios::out | ios::app); //opens/creates new file in peopleFile location, and appends to it.

    int vectorSize = list.size();
    for(int i=0; i < vectorSize; i++)
    {
        //writes person i from person list to file.
        writeSinglePersonToOpenFile(list[i], file);
    }
    file.close();
}

//writeSinglePersonToOpenFile takes person and output file as parameter
void Data::writeSinglePersonToOpenFile(Person& p, ofstream& out)
{
    string name = p.getName(), nationality = p.getNationality();

    //swap out all whitespace characters for underscore so reading from the file can see multi word strings
    replace( name.begin(), name.end(), ' ', '_');
    replace( nationality.begin(), nationality.end(), ' ', '_');

    out << "\n" << name << " " << p.getGender() << " " << p.getBirthYear() << " " << p.getDeathYear() << " " << nationality;
}
//clears both person list and peopleFile
//essentially our version of "drop table"
void Data::clearPersonInDataBase()
{
   list.clear();
   rewriteDataFile();
}

//swapPersonsInDatabase overwrites originalPerson with newPerson
void Data::swapPersonsInDatabase(Person& originalP, Person& newP)
{
    //used when editing the list, so that the person you edited stays in the same
    //spot in the list instead of being added to the bottom of the list
    for(int i=0; i < list.size(); i++)
    {
        if(list[i] == originalP)
        {
            list[i] = newP;
            rewriteDataFile();
            break;
        }
    }
}

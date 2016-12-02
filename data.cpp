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

vector<Person> Data::getList()
{
    return list;
}

void Data::updateSort(vector<Person> pList)
{
    list = pList;
}

void Data::writePersonToFile(Person p)
{
    //open and write in file
    ofstream file;
    file.open(peopleFile, ios::out | ios::app);

    writeSinglePersonToOpenFile(p, file);

    list.push_back(p);

    file.close();
}

void Data::readPeopleFromFile()
{
    //open and read from file, done every time the program is launched

    list.clear();

    ifstream file;
    file.open(peopleFile);
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof();

    string name = "", nationality = "";
    char gender = ' ';
    int bYear = 0, dYear = 0;

    while(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty )
    {

        file >> name >> gender >> bYear >> dYear >> nationality;

        replace( name.begin(), name.end(), '_', ' ');
        replace( nationality.begin(), nationality.end(), '_', ' ');

        Person newPerson(name, gender, bYear, dYear, nationality);
        list.push_back(newPerson);

    }  
    file.close();
}

Config Data::getConfig(){
    return config;
}

void Data::writeConfigToFile(Config c)
{
    //open and write in file
    ofstream file;
    file.open("../T113VLN1/database/settings.txt");

    file << "\n" << c.sortColumn << " " << c.SortOrder;

    config.sortColumn = c.sortColumn;
    config.SortOrder = c.SortOrder;

    file.close();
}

void Data::readConfigFromFile(){

    ifstream file;
    file.open("../T113VLN1/database/settings.txt");
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof();

    string sortOrder = "";
    string sortColumn = "";

    while(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty )
    {
        file >> sortColumn >> sortOrder;

        config.sortColumn = sortColumn;
        config.SortOrder = sortOrder;
    }
    file.close();
}

void Data::removePersonFromDatabase(Person personToRemove)
{
    //make changes to the vector holding people
    int vectorSize = list.size();
    for(int i=0; i < vectorSize; i++)
    {
        if(list[i] == personToRemove)
        {
            list.erase(list.begin()+i);
            break;
        }
    }
    rewriteDataFile();
}

void Data::rewriteDataFile()
{
    //rewrite the entire file with with the changes made to the list vector
    remove(peopleFile.c_str());

    ofstream file;
    file.open(peopleFile, ios::out | ios::app);

    int vectorSize = list.size();
    for(int i=0; i < vectorSize; i++)
    {
        writeSinglePersonToOpenFile(list[i], file);
    }
    file.close();
}

void Data::writeSinglePersonToOpenFile(Person& p, ofstream& out)
{

    string name = p.getName(), nationality = p.getNationality();
    char gender = p.getGender();
    int bYear = p.getBirthYear();
    int dYear = p.getDeathYear();

    //swap out all space characters for underscore so reading from the file can see multi word names
    replace( name.begin(), name.end(), ' ', '_');
    replace( nationality.begin(), nationality.end(), ' ', '_');

    out << "\n" << name << " " << gender << " " << bYear << " " << dYear << " " << nationality;
}

void Data::clearPersonInDataBase()
{
   list.clear();
   rewriteDataFile();
}

void Data::swapPersonsInDatabase(Person& originalP, Person& newP)
{
    int vectorSize = list.size();
    //used when editing the list, so that the person you edited stays in the same
    //spot in the list instead of being added to the bottom of the list
    for(int i=0; i < vectorSize; i++)
    {
        if(list[i] == originalP)
        {
            list[i] = newP;
            break;
        }
    }
    rewriteDataFile();
}

#include "data.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "person.h"

using namespace std;
//data layer

Data::Data()
{
    readPeopleFromFile();
}

vector<Person> Data::getList(){
    return list;
}

void Data::updateSort(vector<Person> pList){
    list = pList;
}

void Data::writePersonToFile(Person p){
    ofstream file;
    file.open("../T113VLN1/database/people.txt", ios::out | ios::app);



    writeSinglePersonToOpenFile(p, file);

    list.push_back(p);

    file.close();

};

void Data::readPeopleFromFile(){

    list.clear();

    ifstream file;
    file.open("../T113VLN1/database/people.txt");
    bool fileIsEmpty = file.peek() == ifstream::traits_type::eof();

    string name = "", nationality = "";
    char gender = ' ';
    int bYear = 0, dYear = 0;

    while(!file.eof() && file.is_open() && !file.fail() && !fileIsEmpty ){

        file >> name >> gender >> bYear >> dYear >> nationality;

        replace( name.begin(), name.end(), '_', ' ');
        replace( nationality.begin(), nationality.end(), '_', ' ');

        Person newPerson(name, gender, bYear, dYear, nationality);
        list.push_back(newPerson);

    }
    file.close();

}

void Data::removePersonFromDatabase(Person personToRemove)
{
    int vectorSize = list.size();
    for(int i=0; i < vectorSize; i++)
    {
        if(list[i] == personToRemove)
        {
            list.erase(list.begin()+i);
        }
    }

    rewriteDataFile();
}

void Data::rewriteDataFile()
{
    remove("../T113VLN1/database/people.txt");

    ofstream file;
    file.open("../T113VLN1/database/people.txt", ios::out | ios::app);

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
    for(int i=0; i < vectorSize; i++)
    {
        if(list[i] == originalP)
        {
            list[i] = newP;
        }
    }
    rewriteDataFile();
}

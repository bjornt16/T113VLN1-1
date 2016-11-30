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

    string name = p.getName(), nationality = p.getNationality();
    char gender = p.getGender();
    int bYear = p.getBirthYear();
    int dYear = p.getDeathYear();

    replace( name.begin(), name.end(), ' ', '_');
    name.erase(name.begin());
    replace( nationality.begin(), nationality.end(), ' ', '_');
    nationality.erase(nationality.begin());

    file << "\n" << name << " " << gender << " " << bYear << " " << dYear << " " << nationality;

    list.push_back(p);

    file.close();

};

void Data::readPeopleFromFile(){

    list.clear();

    ifstream file;
    file.open("../T113VLN1/database/people.txt");

    string name, nationality;
    char gender;
    int bYear, dYear;

    while(!file.eof() && file.is_open() && !file.fail()){

        file >> name >> gender >> bYear >> dYear >> nationality;

        replace( name.begin(), name.end(), '_', ' ');
        replace( nationality.begin(), nationality.end(), '_', ' ');

        Person newPerson(name, gender, bYear, dYear, nationality);
        list.push_back(newPerson);

    }
    file.close();

}

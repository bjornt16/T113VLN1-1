#include "data.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "person.h"

using namespace std;
//data layer
    readPeopleFromFile();
Data::Data()
{

}

vector<Person> Data::getList(){
    return list;
}

void Data::writePersonToFile(Person p){
    ofstream file;
    file.open("database/people.txt");

    string name = p.getName();
    char gender = p.getGender();
    int bYear = p.getBirthYear();
    int dYear = p.getDeathYear();
    string newLine = "\n";

    file << name;
    file << gender;
    file << bYear;
    file << dYear;
    file << newLine;

    list.push_back(p);

    file.close();
};

void Data::readPeopleFromFile(){



    ifstream file;
    file.open("../T113VLN1/database/people.txt");

    string name, nationality;
    char gender;
    int bYear, dYear;

    while(!file.eof() && file.is_open() && !file.fail()){

        file >> name;
        file >> gender;
        file >> bYear;
        file >> dYear;
        file >> nationality;

        Person newPerson(name, gender, bYear, dYear, nationality);
        list.push_back(newPerson);
    }
    file.close();

}

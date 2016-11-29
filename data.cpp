#include "data.h"
#include <iostream>
#include <fstream>

#include "person.h"

using namespace std;
//data layer

Data::Data()
{

}

void Data::writePersonToFile(Person p){
    ifstream file;
    file.open("database/people.txt");

    string name = p.getName();
    char gender = p.getGender();
    int bYear = p.getBirthYear();
    int dYear = p.getDeathYear();
    string newLine = "\n";

    file >> name;
    file >> gender;
    file >> bYear;
    file >> dYear;
    file >> newLine;

    file.close();
};

#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

//Poco (plain old class object)

class Person
{
public:
    Person();
    Person(string n);

    string getName() const;

    int getAge() const;

    char getGender() const;

    string getNationality() const;

private:
    string name;
    int    birthYear;
    int    deathYear;
    char   gender;
    string nationality;

};

#endif // PERSON_H

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

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return deathYear - birthYear;
    }

private:
    string name;
    int    birthYear;
    int    deathYear;
    char   gender;

};

#endif // PERSON_H

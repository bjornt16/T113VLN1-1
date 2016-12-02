#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person
{
public:
    //default constructor
    //requires name, gender, birthyear, deathyear, nationality
    Person(string n, char g, int bY, int dY, string nat);

    //set functions for editing
    void setName(string inputName);
    void setGender(char inputGender);
    void setBY(int inputBY);
    void setDY(int inputDY);
    void setNationality(string inputNat);

    //returns name of Person
    string getName() const;

    //returns only first name instants of Person
    string getFirstName() const;

    //returns only last name instants of Person
    string getLastName() const;

    //calculates and returns age. Calculates from death year if the person
    //is dead, but from current year if the person is still alive.
    int getAge() const;

    //returns birth year
    int getBirthYear() const;

    //returns death year
    int getDeathYear() const;

    //returns gender: F for female and M for male.
    char getGender() const;

    //returns the nationality
    string getNationality() const;

    //Friend functions:
    friend bool operator== (const Person lhs, const Person rhs);

private:
    string name;
    int    birthYear;
    int    deathYear;
    char   gender;
    string nationality;
};

#endif // PERSON_H

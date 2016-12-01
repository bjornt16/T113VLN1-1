#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person
{
public:
    //Constructor:
    Person(string n, char g, int bY, int dY, string nat);

    //set functions for sorting
    void setName(string inputName);
    void setGender(char inputGender);
    void setBY(int inputBY);
    void setDY(int inputDY);
    void setNationality(string inputNat);

    //Member functions:
    string getName() const;
        //returns name of Person

    string getFirstName() const;
        //returns only first name instants of Person

    string getLastName() const;
        //returns only last name instants of Person

    int getAge() const;
        //calculates and returns age. Calculates from death year if the person
        //is death, but from current year if the person is alive.

    int getBirthYear() const;
        //returns birth year

    int getDeathYear() const;
        //returns death year

    char getGender() const;
        //returns gender: F for female and M for male.

    string getNationality() const;
        //returns the nationality

    //Friend functions:
    friend bool operator== (const Person lhs, const Person rhs);

private:
    //Member parameters:
    string name;
    int    birthYear;
    int    deathYear;
    char   gender;
    string nationality;
};



#endif // PERSON_H

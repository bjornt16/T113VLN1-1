#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person
{
public:
    //Constructor:
    Person(string n, char g, int bY, int dY, string nat);

    //set föll fyrir sorting
    void setName(string inputName);
    void setGender(char inputGender);
    void setBY(int inputBY);
    void setDY(int inputDY);
    void setNationality(string inputNat);

    //Member föll:
    string getName() const;
        //skilar nafni instants af Person

    string getFirstName() const;
        //skilar aðeins fyrsta nafn instants af Person

    string getLastName() const;
        //skilar aðeins seinasta nafn instants af Person

    int getAge() const;
        //reiknar út og skilar aldur. Reiknað frá dánarári ef viðkomandi er
        //látinn en frá núverandi ári ef viðkomandi er lifandi.

    int getBirthYear() const;
        //skilar fæðingarári.

    int getDeathYear() const;
        //skilar dánarári.

    char getGender() const;
        //skilar F fyrir female og M fyrir male.

    string getNationality() const;
        //skilar upprunalandi viðkomandi.

private:
    //Member breytur:
    string name;
    int    birthYear;
    int    deathYear;
    char   gender;
    string nationality;
};

#endif // PERSON_H

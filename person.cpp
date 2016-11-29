#include "person.h"

//poco

Person::Person()
{

}

 Person::Person(string n, char g, int bY, int dY, string nat)
{
    isAlive = 0;
    name = n;
    gender = g;
    birthYear = bY;
    deathYear = dY;
    nationality = nat;
}

 Person::Person(string n, char g, int bY, string nat)
{
    isAlive = 0;
    name = n;
    gender = g;
    birthYear = bY;
    nationality = nat;
}

 string Person::getName() const
 {
     return name;
 }

 int Person::getAge() const
 {
     if(isAlive)
     {
        return (1900 + tm_year) - birthYear; //tm_year nær í ártal talið frá 1900.
     }
     return deathYear - birthYear;
 }

 int Person::getBirthYear() const
 {
     return birthYear;
 }

 int Person::getDeathYear() const
 {
     return deathYear;
 }

 char Person::getGender() const
 {
     return gender;
 }

 string Person::getNationality() const
 {
     return nationality;
 }

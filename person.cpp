#include "person.h"

//poco

Person::Person()
{

}

 Person::Person(string n, char g, int bY, int dY, string nat)
{
    name = n;
    gender = g;
    birthYear = bY;
    deathYear = dY;
    nationality = nat;
}

 string Person::getName() const
 {
     return name;
 }

 int Person::getAge() const
 {
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

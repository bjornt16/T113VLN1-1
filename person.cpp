#include "person.h"

//poco

Person::Person()
{

}

 Person::Person(string n)
{
    name = n;
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

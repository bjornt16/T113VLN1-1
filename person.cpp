#include "person.h"
#include <time.h>
#include <cstddef>

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

 string Person::getFirstName() const
 {
     return name.substr(0, name.find(" "));
 }

 string Person::getLastName() const
 {
     return name.substr(name.rfind(" ") + 1);
 }

 int Person::getAge() const
 {
     if(deathYear == 0)
     {
         time_t t = time(NULL);
         tm* timePtr = localtime(&t);
         int currentYear = timePtr->tm_year + 1900;
         return currentYear - birthYear;
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

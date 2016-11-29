#include "person.h"
#include <time.h>

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
    isAlive = 1;
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
<<<<<<< HEAD
        //return (1900 + tm_year) - birthYear; //tm_year nær í ártal talið frá 1900.
=======
         time_t currentTime;
         tm* lt = localtime(&currentTime);
         int currentYear = 1900 + lt->tm_year;
         return currentYear - birthYear; //tm_year nær í ártal talið frá 1900.
>>>>>>> origin/master
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

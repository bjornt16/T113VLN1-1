#include "person.h"
#include <time.h>
#include <stdlib.h>

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
         time_t currentTime;
         tm* lt = localtime(&currentTime);
         int currentYear = 1900 + lt->tm_year;
         return currentYear - birthYear;
     }
     return deathYear - birthYear;
 }

 int Person::getBirthYear() const
 {
     return birthYear;
 }

 string Person::getDeathYear() const
 {
     string strDYear;
     if(isAlive)
     {
         strDYear = '-';
     }else{
         strDYear = to_string(deathYear);
     }
     return strDYear;
 }

 char Person::getGender() const
 {
     return gender;
 }

 string Person::getNationality() const
 {
     return nationality;
 }

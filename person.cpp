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

 char Person::getGender() const
 {
     return gender;
 }

 string Person::getNationality() const
 {
     return nationality;
 }

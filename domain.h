#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include "person.h"
#include "data.h"

using namespace std;

//domain layer

class Domain
{
private:
    Data data;
public:
    Domain();
    vector<Person> getPersonList(/* TODO: parameters */);

    //Search functions based on what you want type of search you want to do
    vector<Person> searchPersonName(string search);           //name
    vector<Person> searchPersonNationality(string search);    //nationality
    vector<Person> searchPersonGender(char search);           //gender
    vector<Person> searchPersonBirth(int from, int to = 9999);//birth year
    vector<Person> searchPersonDeath(int from, int to = 9999);//death year

    //Sort functions based on what you want to sort by
    vector<Person> sortPeopleByName(string sortOrder = "asc");  // name
    vector<Person> sortPeopleByGender(string sortOrder = "asc");// gender
    vector<Person> sortPeopleByBY(string sortOrder = "asc");    // birth year
    vector<Person> sortPeopleByDY(string sortOrder = "asc");    // death year
    vector<Person> sortPeopleByNat(string sortOrder = "asc");   // nationality

    void addPerson(Person p);
};

#endif // Domain_H

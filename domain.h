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

    vector<Person> searchPersonName(string search);
    vector<Person> searchPersonNationality(string search);
    vector<Person> searchPersonGender(char search);
    vector<Person> searchPersonBirth(int from, int to = 9999);
    vector<Person> searchPersonDeath(int from, int to = 9999);

    void addPerson(Person p);
};

#endif // Domain_H

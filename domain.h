#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include "person.h"
#include "data.h"

using namespace std;

//domain layer

class Domain
{
public:
    Domain();

    Data data;
    vector<Person> getPeople(/* TODO: parameters */);
    void addPerson(Person p);
};

#endif // Domain_H

#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include "person.h"

using namespace std;

//domain layer

class Domain
{
public:
    Domain();

    //
    vector<Person> getPeople(/* TODO: parameters */);

    vector<Person> savedPeople();
};

#endif // Domain_H

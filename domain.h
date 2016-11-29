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
};

#endif // Domain_H

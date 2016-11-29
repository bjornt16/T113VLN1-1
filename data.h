#ifndef DATA_H
#define DATA_H

#include "person.h"

using namespace std;

//data layer

class Data
{
public:
    Data();

    void writePersonToFile(Person P);
};

#endif // DATA_H

#ifndef DATA_H
#define DATA_H
#include <vector>
#include "person.h"

using namespace std;

//data layer

class Data
{
public:
    Data();

    vector<Person> list;
    vector<Person> getList();
    void writePersonToFile(Person P);
    void readPeopleFromFile();
};

#endif // DATA_H

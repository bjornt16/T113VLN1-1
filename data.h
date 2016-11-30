#ifndef DATA_H
#define DATA_H
#include <vector>
#include "person.h"

using namespace std;

//data layer

class Data
{
private:
    //vectorinn sem heldur utan um listann í heild sinni
    vector<Person> list;
public:
    Data();

    vector<Person> getList();
    void writePersonToFile(Person P);
    void updateSort(vector<Person> pList);
    void readPeopleFromFile();

    void removePersonFromDatabase(Person personToRemove);
        // hendir personToRemove úr vectornum og database.

    void rewriteDatafile();
        //yfirskrifar gögn í people.txt

    void writeSinglePersonToOpenFile(Person p, ofstream& out);
        //skrifar Person p í file. Þarf að vera búið að opna file fyrir og senda inn ostream
};

#endif // DATA_H

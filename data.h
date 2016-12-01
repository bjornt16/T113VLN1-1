#ifndef DATA_H
#define DATA_H
#include <vector>
#include "person.h"

using namespace std;

//data layer

class Data
{
private:
    //vector contains the list
    vector<Person> list;
public:
    Data();

    vector<Person> getList();
    void writePersonToFile(Person P);
    void updateSort(vector<Person> pList);
    void readPeopleFromFile();

    void removePersonFromDatabase(Person personToRemove);
        // removes personToRemove from the vector and database.

    void rewriteDatafile();
        //overwrites data in people.txt

    void writeSinglePersonToOpenFile(Person p, ofstream& out);
    //writes person p in file. Opens the file before and use ostream

    void editPersonInDatabase(Person personToEdit);
        //Edits personToEdit in vector and database.

};

#endif // DATA_H

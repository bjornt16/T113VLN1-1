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

        //removes personToRemove from the vector and database.
    void removePersonFromDatabase(Person personToRemove);

        //overwrites data in people.txt
    void rewriteDatafile();

        //writes person p in file. Opens the file before and use ostream
    void writeSinglePersonToOpenFile(Person p, ofstream& out);

         //Edits personToEdit in vector and database
    void editPersonInDatabase(Person personToEdit);

        //Clears everything from the list
    void clearPersonInDataBase();

};

#endif // DATA_H

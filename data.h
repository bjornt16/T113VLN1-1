#ifndef DATA_H
#define DATA_H

#include <vector>
#include "person.h"
#include "config.h"

using namespace std;

//data layer

class Data
{
private:
    //vector contains the list
    vector<Person> list;
    const string peopleFile = "../T113VLN1/database/people.txt";
    Config config;
public:
    Data();

    vector<Person> getList();

    //writes information stored in vector<Person> list to a file
    void writePersonToFile(Person P);

    void updateSort(vector<Person> pList);

    //reads information stored inside a file and puts it into vector
    void readPeopleFromFile();

    //removes personToRemove from the vector and database.
    void removePersonFromDatabase(Person personToRemove);

    //overwrites data in people.txt
    void rewriteDataFile();

    //writes person p in file. Opens the file before and use ostream
    void writeSinglePersonToOpenFile(Person& p, ofstream& out);

    //Edits personToEdit in vector and database
    void editPersonInDatabase(Person personToEdit);

    //Clears everything from the list
    void clearPersonInDataBase();

    void swapPersonsInDatabase(Person& originalP, Person& newP);

    void readConfigFromFile();
    void writeConfigToFile(Config c);
    Config getConfig();
};

#endif // DATA_H

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

    const string directoryPath = "../T113VLN1/database/";

    //people file path
    const string peopleFile = directoryPath+"people.txt";
    //config file path
    const string configFile = directoryPath+"config.txt";

    //confic class contains config settings.
    Config config;
public:
    //default constructor
    Data();

    //getList returns main person list
    vector<Person> getList();

    //writePersonTofile takes a person class as parameter, and adds it to both the main person vector, and people.txt file
    void writePersonToFile(Person P);

    //reads information stored inside a file and puts it into the main person vector
    void readPeopleFromFile();

    //removePersonFromDatabase takes a person as variable, if identical person exists in the database, it is removed from both main vector and people.txt
    void removePersonFromDatabase(Person personToRemove);

    //overwrites data in people.txt
    void rewriteDataFile();

    //writes person to people.txt file. Opens the file before and use ostream
    void writeSinglePersonToOpenFile(Person& p, ofstream& out);

    //editPersonInDatabase takes a person as variable, if identical person exists in the database, it is overwritten in both main vector and people.txt
    void editPersonInDatabase(Person personToEdit);

    //Clears everything from the list
    //drops table, essentially
    void clearPersonInDataBase();

    //swapPersonsInDatabase overwrites originalPerson with newPerson
    void swapPersonsInDatabase(Person& originalP, Person& newP);

    //readConfigFromFile reads saved settings from config.txt, and puts them in Data.config for easy access
    void readConfigFromFile();

    //writeConfigToFile overwrites config.txt with new settings.
    void writeConfigToFile(Config c);

    //getConfig makes config settings accessable in other layers, returns copy of config.
    Config getConfig();
};

#endif // DATA_H

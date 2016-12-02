#ifndef CONFIG_H
#define CONFIG_H
#include <string>

using namespace std;


//poco class that holds config settings;
class Config
{
public:
    Config(); //default constructor
    Config(string sO, int sC); //constructor with 2 parameters usage example ("asc",1)
    string SortOrder;  //sort order, either "asc" or "desc"
    int sortColumn;    //sortColumn corresponds to the column position in the list from left to right.
};

#endif // CONFIG_H

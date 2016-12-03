#include "config.h"

//Poco class to hold, config settings;

//default constructor
Config::Config()
{
    SortOrder = "asc";
    sortColumn = 1;
}


//constructor that takes 2 parameters example ("asc",1);
Config::Config(string sO, int sC)
{
    SortOrder = sO;
    sortColumn = sC;
}

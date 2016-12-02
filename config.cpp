#include "config.h"

Config::Config()
{
    SortOrder = "asc";
    sortColumn = "name";
}

Config::Config(string sO, string sC){
    SortOrder = sO;
    sortColumn = sC;
}

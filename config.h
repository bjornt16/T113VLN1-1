#ifndef CONFIG_H
#define CONFIG_H
#include <string>

using namespace std;


class Config
{
public:
    Config();
    Config(string sO, string sC);
    string SortOrder;
    string sortColumn;
};

#endif // CONFIG_H

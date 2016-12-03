#include "config.h"
#include "domain.h"
#include "data.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//domain layer
Domain::Domain()
{

}

//Function used for adding a person to the list vector
//passes a person to the data layer for processing
void Domain::addPerson(Person p)
{
    data.writePersonToFile(p);
}

//Gets the vector that holds the Persons from the data layer
vector<Person> Domain::getPersonList()
{
    return data.getList();
}

//Gets the config object that holds the config settings from the data layer
Config Domain::getConfig()
{
    return data.getConfig();
}

//passes a config object to the data layer for processing
//overwrite old config
void Domain::setConfig(Config c)
{
    data.writeConfigToFile(c);
};

//searchPersonName takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonName(vector<Person> people, string search)
{
    vector<Person> searchList;

    for(size_t i= 0; i < people.size(); i++ )
    {
        string name = people[i].getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(search.begin(), search.end(), search.begin(), ::tolower);

        if(search.find(' ') != string::npos)
        {
            search.erase(search.begin());
        }

        if(name.find(search) != string::npos)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}

//searchPersonNationality takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonNationality(vector<Person> people, string search)
{
    vector<Person> searchList;

    for(size_t i= 0; i < people.size(); i++ )
    {
        string nationality = people[i].getNationality();
        transform(nationality.begin(), nationality.end(), nationality.begin(), ::tolower);
        transform(search.begin(), search.end(), search.begin(), ::tolower);

        if(nationality.find(search) != string::npos)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}

//searchPersonGender takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonGender(vector<Person> people, char search)
{
    vector<Person> searchList;

    for(size_t i= 0; i < people.size(); i++ )
    {
        char gender = people[i].getGender();
        gender = (tolower(gender));
        search = (tolower(search));
        if(search == gender)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}

//searchPersonBirth takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonBirth(vector<Person> people, int from, int to)
{
    vector<Person> searchList;

    if(to == dummyNull)
    {
        to = from;
    }

    for(size_t i= 0; i < people.size(); i++ )
    {
        int birthYear = people[i].getBirthYear();

        if(birthYear >= from && birthYear <= to)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}

//searchPersonDeath takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonDeath(vector<Person> people, int from, int to)
{
    vector<Person> searchList;

    if(to == dummyNull)
    {
        to = from;
    }

    for(size_t i= 0; i < people.size(); i++ )
    {
        int deathYear = people[i].getDeathYear();

        if(deathYear >= from && deathYear <= to && deathYear != 0)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;
}

//searchPersonAge takes in a vector of person to search in, and a search parameter.
//returns a vector of persons
vector<Person> Domain::searchPersonAge(vector<Person> people, int from, int to)
{
    vector<Person> searchList;

    if(to == dummyNull)
    {
        to = from;
    }

    for(size_t i= 0; i < people.size(); i++ )
    {
        int age = people[i].getAge();

        if(age >= from && age <= to)
        {
            searchList.push_back(people[i]);
        }
    }

    return searchList;

}
//sortPersonByDefault takes in a vector of person and returns it sorted in the saved default sort order
vector<Person> Domain::sortPersonByDefault(vector<Person> pList)
{
    Config config = data.getConfig();
    vector<Person> sortedList;
    switch(config.sortColumn)
    {
        case 1 :
        {
            sortedList = sortPersonByName(config.SortOrder, pList);
            break;
        }
        case 2 :
        {
            sortedList = sortPersonByGender(config.SortOrder, pList);
            break;
        }
        case 3 :
        {
            sortedList = sortPersonByBY(config.SortOrder, pList);
            break;
        }
        case 4 :
        {
            sortedList = sortPersonByDY(config.SortOrder, pList);
            break;
        }
        case 5 :
        {
            sortedList = sortPersonByNat(config.SortOrder, pList);
            break;
        }
        case 6 :
        {
            sortedList = sortPersonByAge(config.SortOrder, pList);
            break;
        }
        default : {
            break;
        }
    }

    return sortedList;

}

//sortPersonByName takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByName(string sortOrder, vector<Person> pList)
{
    struct PersonAsc
    {
        bool operator() (Person i,Person j)
        {
        return (i.getName()<j.getName());
        }
    };

    struct PersonDesc
    {
        bool operator() (Person i,Person j)
        {
        return (i.getName()>j.getName());
        }
    };

    //sorting people asc is baseline search
    if(sortOrder == "asc")
    {
        PersonAsc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }
    //desc sorting if user specifically asks for desc sort
    else if(sortOrder == "desc")
    {
        PersonDesc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }

    return pList;
}

//sortPersonByGender takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByGender(string sortOrder, vector<Person> pList)
{

    struct PersonAsc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getGender() < j.getGender());
        }
    };

    struct PersonDesc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getGender() > j.getGender());
        }
    };

    //sorting people asc is baseline search
    if(sortOrder == "asc")
    {
        PersonAsc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }
    //desc sorting if user specifically asks for desc sort
    else if(sortOrder == "desc")
    {
        PersonDesc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }

    return pList;
}

//sortPersonByBY takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByBY(string sortOrder, vector<Person> pList)
{
    struct PersonAsc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getBirthYear() < j.getBirthYear());
        }
    };

    struct PersonDesc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getBirthYear() > j.getBirthYear());
        }
    };

    //sorting people asc is baseline search
    if(sortOrder == "asc")
    {
        PersonAsc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }
    //desc sorting if user specifically asks for desc sort
    else if(sortOrder == "desc")
    {
        PersonDesc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }

    return pList;
}

//sortPersonByDY takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByDY(string sortOrder, vector<Person> pList)
{

    struct PersonAsc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getDeathYear() < j.getDeathYear());
        }
    };

    struct PersonDesc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getDeathYear() > j.getDeathYear());
        }
    };

    //sorting people asc is baseline search
    if(sortOrder == "asc")
    {
        PersonAsc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }
    //desc sorting if user specifically asks for desc sort
    else if(sortOrder == "desc")
    {
        PersonDesc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }

    return pList;
}

//sortPersonByNat takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByNat(string sortOrder, vector<Person> pList)
{

    struct PersonAsc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getNationality() < j.getNationality());
        }
    };

    struct PersonDesc
    {
        bool operator() (Person i,Person j)
        {
            return (i.getNationality() > j.getNationality());
        }
    };

    //sorting people asc is baseline search
    if(sortOrder == "asc")
    {
        PersonAsc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }
    //desc sorting if user specifically asks for desc sort
    else if(sortOrder == "desc")
    {
        PersonDesc cmp;
        sort(pList.begin(), pList.end(), cmp);
    }

    return pList;
}

//sortPersonByAge takes in a vector of person to sort, and a sort order ("desc or "asc).
vector<Person> Domain::sortPersonByAge(string sortOrder, vector<Person> pList)
{

        struct PersonAsc
        {
            bool operator() (Person i,Person j)
            {
                return (i.getAge() < j.getAge());
            }
        };

        struct PersonDesc
        {
            bool operator() (Person i,Person j)
            {
                return (i.getAge() > j.getAge());
            }
        };

        //sorting people asc is baseline search
        if(sortOrder == "asc")
        {
            PersonAsc cmp;
            sort(pList.begin(), pList.end(), cmp);
        }
        //desc sorting if user specifically asks for desc sort
        else if(sortOrder == "desc")
        {
            PersonDesc cmp;
            sort(pList.begin(), pList.end(), cmp);
        }

        return pList;
}

//Function that calls data.removePersonFromDatabase and deletes personToRemove from vector and database
//passes a person class to the data layer for processing
void Domain::removePerson(Person personToRemove)
{
    data.removePersonFromDatabase(personToRemove);
}

//Function that calls data.editPersonInDatabase to edit a Person.
//passes a person class to the data layer for processing
void Domain::editPerson(Person personToEdit)
{
    data.removePersonFromDatabase(personToEdit);
}

//Function that calls data.clearPersonInDatabase to clear everything in the list.
void Domain::clearPerson()
{
    data.clearPersonInDataBase();
}

//Calls the function data.swapPersonsInDatabase to swap originalP with newP
void Domain::swapPerson(Person& originalP, Person& newP)
{
    data.swapPersonsInDatabase(originalP, newP);
}

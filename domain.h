#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include "person.h"
#include "data.h"

using namespace std;

//domain layer

class Domain
{
private:
    Data data;
public:
    Domain();
         //Gets the vector that holds the Persons
    vector<Person> getPersonList();

        //Function that uses data.removePersonFromDatabase and deletes personToRemove from vector and database
    void removePerson(Person personToRemove);

         //Function that uses data.editPersonInDatabase to edit a Person.
    void editPerson(Person personToEdit);

        //Function that uses data.clearPersonInDatabase to clear everything in the list.
    void clearPerson();

        //Calls the function data.swapPersonsInDatabase to originalP with newP
    void swapPersons(Person& originalP, Person& newP);


    //Search functions based on what you want type of search you want to do
    vector<Person> searchPersonName(vector<Person> people, string search);           //name
    vector<Person> searchPersonNationality(vector<Person> people, string search);    //nationality
    vector<Person> searchPersonGender(vector<Person> people, char search);           //gender
    vector<Person> searchPersonBirth(vector<Person> people, int from, int to = 9999);//birth year
    vector<Person> searchPersonDeath(vector<Person> people, int from, int to = 9999);//death year

    //Sort functions based on what you want to sort by
    vector<Person> sortPeopleByName(string sortOrder);  // name
    vector<Person> sortPeopleByGender(string sortOrder);// gender
    vector<Person> sortPeopleByBY(string sortOrder);    // birth year
    vector<Person> sortPeopleByDY(string sortOrder);    // death year
    vector<Person> sortPeopleByNat(string sortOrder);   // nationality


    void addPerson(Person p);
};

#endif // Domain_H

#ifndef UI_H
#define UI_H

#include "domain.h"
#include <vector>
#include "person.h"


//presentation layer

class UI
{
private:
    Domain domain;

    //prentar út listann, listinn breytist eftir því hvernig er verið að prenta hann
    //það er kallað í þetta fall út frá öðrum föllum td í search þegar listinn á að vera birtur með ákveðnum úttökum
    void ListPerson(vector<Person> people, bool search = 0);

    //bæta persónu í listann
    void addPerson();

    //leitar að persónu
    void searchPerson();

    //fall sem gengur frá röðun í listanum
    void sortPeople();

    //fall sem annaðhvort eyðir öllum listanum eða eyðir einu staki úr listanum
    void removePerson();

    //fall sem leyfir notandanum að breyta listanum
    void editPerson();
public:
    UI();

    // Displays the main menu of the program.
    void mainMenu();
};

#endif // CONSOLEUI_H

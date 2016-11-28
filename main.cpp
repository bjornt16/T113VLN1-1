#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Programmer
{

private:
    string newName;
    char newGender;
    int newB_year;
    int newD_year;
};


void disp_funct()
{

}

void add_funct(vector<Programmer> programmers)
{
    string name;
    char gender;
    int b_year;
    int d_year;

    cout << "Name: ";
    cin >> name;
    cout << "gender: ";
    cin >> gender;
    cout << "Birth year: ";
    cin >> b_year;
    cout << "Death year: ";
    cin >> d_year;


    fstream the_file;
    the_file.open("programmers.txt");
    the_file >> name;
    the_file >> gender;
    the_file >> b_year;
    the_file >> d_year;
}


int main()
{
    vector<Programmer> programmers;
    char add_or_display = ' ';
    while(1)
    {
        cout << "Press 'A' to add, 'D' to display or 'Q' to quit: ";
        cin >> add_or_display;

        if(add_or_display == 'a' || add_or_display == 'A')
        {
            add_funct(programmers);
        }
        else if(add_or_display == 'd' || add_or_display == 'D')
        {
            disp_funct();
        }
        else if (add_or_display == 'q' || add_or_display == 'Q')
        {
            return 0;
        }
        else
        {
            cout << "Invalid input, try again" << endl;
        }
    }

    return 0;
}

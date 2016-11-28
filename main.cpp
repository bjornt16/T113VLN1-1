#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Programmer
{

};


void disp_funct()
{

}

void add_funct()
{

}


int main()
{
    char add_or_display = ' ';
    while(1)
    {
        cout << "Press 'A' to add, 'D' to display or 'Q' to quit: ";
        cin >> add_or_display;

        if(add_or_display == 'a' || add_or_display == 'A')
        {
            add_funct();
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

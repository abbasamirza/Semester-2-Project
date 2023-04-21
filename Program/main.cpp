#include <iostream>
#include <conio.h>
using namespace std;


/* CLASS DEFINITIONS START HERE */
class User
{
    protected:
        string name, NIC, password, dateofbirth;

    public:

};
/* CLASS DEFINITIONS END HERE */


/* FUNCTION PROTOTYPES START HERE */
void get_loginOrSignup(int*);
string get_NIC();
/* FUNCTION PROTOTYPES END HERE */


/* MAIN FUNCTION STARTS HERE */
int main()
{
    /* Variable Declerations */
    string nic;
    int entry;

    get_loginOrSignup(&entry);
    if (entry == 1)
    {
        nic = get_NIC();
    }

    return 0;
}
/* MAIN FUNCTION ENDS HERE */


/* FUNCTION DEFINITIONS START HERE */
void get_loginOrSignup(int* entry)
{
    cout << "1. Login\n"
        << "2. Signup\n\n"
        << "Enter the number of the action that you want to perform" << endl;
    cin >> *entry;

    while (*entry != 1 && *entry != 2)
    {
        cout << "Invalid option, please re-enter\n";
        cin >> *entry;
    }
}

string get_NIC()
{
    char nic[16];
    int i;

    cout << "Enter your NIC number\n";
    while (1)
    {
        nic[i] = _getch();
        
        if (nic[i] == 13)
        {
            break;
        }
    }

    return "1";
}
/* FUNCTION DEFINITIONS END HERE */
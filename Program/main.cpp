#include <iostream>
#include <conio.h>
using namespace std;

#define LOGIN 1
#define SIGNUP 2
#define EXIT 0

#define ENTER 13
#define BACKSPACE 8

/* CLASS DEFINITIONS START HERE */
class User
{
    protected:
        string name, NIC, password;

    public:

};
/* CLASS DEFINITIONS END HERE */


/* FUNCTION PROTOTYPES START HERE */
int get_loginOrSignup(void);
string get_NIC(void);
/* FUNCTION PROTOTYPES END HERE */


/* MAIN FUNCTION STARTS HERE */
int main(void)
{
    /* Variable Declerations */
    string inputNIC;
    int entry;

    entry = get_loginOrSignup();
    if (entry == LOGIN)
    {
        inputNIC = get_NIC();
    }

    return 0;
}
/* MAIN FUNCTION ENDS HERE */


/* FUNCTION DEFINITIONS START HERE */
int get_loginOrSignup(void)
{
	int entry;
	
    cout << "Enter the number of the action that you want to perform\n\n" 
		<< "1. Login\n"
        << "2. Signup\n"
        << "0. Exit\n" << endl;
    cin >> entry;
	cout << endl;
	
    while (entry != LOGIN && entry != SIGNUP && entry != EXIT)
    {
        cout << "Invalid option, please re-enter\n";
        cin >> entry;
    }
    
    return entry;
}

string get_NIC(void)
{
    char nic[16];
    int i = 0;

    cout << "Enter your NIC number\n";
    while (1)
    {
        nic[i] = _getch();
        
        if (nic[i] == ENTER)
        {
        	if (i == 13)
        	{
        		nic[i] = '\0';
        		break;
			}
			
			else if (i == 0)
			{
				break;
			}
			
			else
			{
				cout << "\nInvalid NIC number please re-enter\n";
				i = 0;
			}
        }
        
        else if (nic[i] == BACKSPACE && i > 0)
        {
        	--i;
        	cout << "\b \b";
		}
		
		else if (nic[i] >= '0' && nic[i] <= '9' && i != 13)
		{
			cout << nic[i++] << " \b";
		}
    }

    return nic;
}
/* FUNCTION DEFINITIONS END HERE */
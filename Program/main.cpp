#include <iostream>
#include <fstream>
#include <string>
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
        friend bool check_NIC(string);
};
/* CLASS DEFINITIONS END HERE */


/* FUNCTION PROTOTYPES START HERE */
int get_loginOrSignup(void);
string get_NIC(void);
string get_name(void);
string get_pass(void);
bool check_NIC(string);
/* FUNCTION PROTOTYPES END HERE */


/* MAIN FUNCTION STARTS HERE */
int main(void)
{
    /* Variable Declerations */
    string inputNIC, inputName, inputPass;
    int entry;
    ofstream out;

    /* Create File If It Does Not Exist */
    out.open("Users.txt", ios::app);

    entry = get_loginOrSignup();
    if (entry == LOGIN)
    {
        inputNIC = get_NIC();
        check_NIC(inputNIC);
    }

    else if (entry == SIGNUP)
    {
        inputNIC = get_NIC();
        inputName = get_name();
        inputPass = get_pass();
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

    cout << "Enter NIC number\n";
    while (true)
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

string inputName(void)
{
    string name;

    cout << "Enter Name: ";
    getline(cin >> ws, name);

    return name;
}

string inputPass(void)
{
    string pass;
    int i = 0;

    cout << "Enter Password: ";
    while (true)
    {
        pass[i] = _getch();

        if (pass[i] == ENTER)
        {
            pass[i] = '\0';
            break;
        }

        else if (pass[i] == BACKSPACE && i > 0)
        {
            --i;
            cout << "\b \b";
        }

        else
        {
            ++i;
            cout << "* \b";
        }
    }
}

bool check_NIC(string inputNIC)
{
    User* user;

    
}
/* FUNCTION DEFINITIONS END HERE */
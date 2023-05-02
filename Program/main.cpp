#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

#define NOTEXISTS -1
#define LOGIN 1
#define SIGNUP 2
#define FORGOT 3
#define EXIT 4
#define ENTER 13
#define BACKSPACE 8
#define BOX 178

/* CLASS DEFINITIONS START HERE */
class OutputScreen
{
    public:
        HANDLE outScreen;
        WORD defaultColor;
        CONSOLE_SCREEN_BUFFER_INFO info;
        int width;

        OutputScreen()
        {
            outScreen = GetStdHandle(STD_OUTPUT_HANDLE);
            width = maximize_outputWindow();
            defaultColor = info.wAttributes;
            SetConsoleTitle("ADMISSION PORTAL");
        }

        int maximize_outputWindow();
        void display_welcomeMsg();
        void display_boxes(int);
        void display_spaces(int);
        void display_defaultMessages();
        void display_loginSuccess();
        void display_randomPassSuccess();
} console;

class User
{
    protected:
        string name, NIC, password;

    public:
        User ()
        {
            name = NIC = password = "";
        }

        void set_name(string name)
        {
            this->name = name;
        }

        void set_NIC(string nic)
        {
            this->NIC = nic;
        }

        void set_password(string pass)
        {
            password = pass;
        }

        string get_name()
        {
            return name;
        }

        string get_NIC()
        {
            return NIC;
        }

        string get_password()
        {
            return password;
        }
};
/* CLASS DEFINITIONS END HERE */

/* FUNCTION PROTOTYPES START HERE */
int get_loginOrSignup();
string get_NIC();
string get_name();
string get_pass();
char get_type();
long long int check_NIC(string);
bool check_pass(string, int);
User create_user(string, string, string);
void generate_random();
string get_randomPass();
bool confirm_generatedPass(string);
/* FUNCTION PROTOTYPES END HERE */

/* MAIN FUNCTION STARTS HERE */
int main()
{
    /* Variable Declerations */
    string inputNIC, inputName, inputPass;
    char inputType;
    int entry, wrongPassCount;
    long long int index;
    ofstream out;

    /* Create File If It Does Not Exist */
    out.open("Users.txt", ios::app);
    out.close();

    console.display_defaultMessages();
    entry = get_loginOrSignup();

    if (entry == LOGIN)
    {
        console.display_defaultMessages();
        inputNIC = get_NIC();
        if (inputNIC != "NIC Number Not Entered")
        {
            index = check_NIC(inputNIC);
            if (index != NOTEXISTS)
            {
                cout << endl << endl;
                wrongPassCount = 3;

                while (wrongPassCount >= 0)
                {
                    inputPass = get_pass();

                    if (check_pass(inputPass, index))
                    {
                        console.display_defaultMessages();
                        console.display_loginSuccess();
                        break;
                    }

                    else
                    {
                        SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);

                        if (wrongPassCount == 0)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\t\tToo many incorrect attempts, exiting program\n";
                            break;
                        }

                        else if (wrongPassCount > 1)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered is incorrect, you have " << wrongPassCount-- << " tries left\n";
                        }

                        else
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered is incorrect, you have " << wrongPassCount-- << " try left\n";
                        }

                        SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                    }
                }
            }

            else
            {
                cout << endl << endl;
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                cout << "\t\t\t\t\t\t\t\tAccount with the entered NIC Number doesnot exist\n\n"; // 8
                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                cout << "\t\t\t\t\t\t\t\t1. Proceed with signup with the entered NIC number\n"
                    << "\t\t\t\t\t\t\t\t2. Go to main menu\n"
                    << "\t\t\t\t\t\t\t\t3. Exit\n\n"
                    << "\t\t\t\t\t\t\t\t-> ";
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                cin >> entry;

                while (entry != 1 && entry != 2 && entry != 3)
                {
                    SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                    cout << "\t\t\t\t\t\t\t\tInvalid option, please re-enter\n"; // 8
                    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                    cout << "\t\t\t\t\t\t\t\t-> ";
                    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                    cin >> entry;
                }

                SetConsoleTextAttribute(console.outScreen, console.defaultColor);

                if (entry == 1)
                {
                    cout << endl << endl;
                    inputName = get_name();
                    cout << endl << endl;
                    inputPass = get_pass();
                    console.display_defaultMessages();
                    User user = create_user(inputName, inputNIC, inputPass);
                }

                else if (entry == 2)
                {
                    main();
                }
            }
        }

        else
        {
            SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
            cout << "\n\n\t\t\t\t\t\t\t\tYou didnot enter a NIC number, exiting program\n\n"; // 8
            SetConsoleTextAttribute(console.outScreen, console.defaultColor);
        }
    }

    else if (entry == SIGNUP)
    {
        console.display_defaultMessages();
        inputNIC = get_NIC();

        if (inputNIC != "NIC Number Not Entered")
        {
            index = check_NIC(inputNIC);
            if (index == NOTEXISTS)
            {
                cout << endl << endl;
                inputName = get_name();
                cout << endl << endl;
                inputPass = get_pass();
                cout << endl << endl;
                inputType = get_type();
                wrongPassCount = 3;

                if (inputType == 'Y' || inputType == 'y')
                {
                    string temp;
                    
                    cout << endl << endl;
                    generate_random();

                    while (wrongPassCount >= 0)
                    {
                        temp = get_randomPass();

                        if (confirm_generatedPass(temp))
                        {
                            cout << endl << endl;
                            console.display_randomPassSuccess();
                            break;
                        }

                        else
                        {
                            SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);

                            if (wrongPassCount == 0)
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tToo many incorrect attempts, exiting program\n";
                                --wrongPassCount;
                                break;
                            }

                            else if (wrongPassCount > 1)
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered does not match the random generated password, you have " << wrongPassCount-- << " tries left\n";
                            }

                            else
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered does not match the random generated password, you have " << wrongPassCount-- << " try left\n";
                            }

                            SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                        }
                    }
                }

                if (wrongPassCount != -1)
                {
                    console.display_defaultMessages();
                    User user = create_user(inputName, inputNIC, inputPass);
                }
            }

            else
            {
                cout << endl << endl;
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                cout << "\t\t\t\t\t\t\t\tAccount with the entered NIC Number already exists\n\n"; // 8
                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                cout << "\t\t\t\t\t\t\t\t1. Proceed with login with the entered NIC number\n"
                    << "\t\t\t\t\t\t\t\t2. Go to main menu\n"
                    << "\t\t\t\t\t\t\t\t3. Exit\n\n"
                    << "\t\t\t\t\t\t\t\t-> ";
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                cin >> entry;

                while (entry != LOGIN && entry != 2 && entry != 3)
                {
                    SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                    cout << "\t\t\t\t\t\t\t\tInvalid option, please re-enter\n" // 8
                        << "\t\t\t\t\t\t\t\t-> ";
                    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                    cin >> entry;
                }

                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                
                if (entry == LOGIN)
                {
                    cout << endl << endl;
                    wrongPassCount = 3;

                    while (wrongPassCount >= 0)
                    {
                        inputPass = get_pass();

                        if (check_pass(inputPass, index))
                        {
                            console.display_defaultMessages();
                            console.display_loginSuccess();
                            break;
                        }

                        else
                        {
                            SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);

                            if (wrongPassCount == 0)
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tToo many incorrect attempts, exiting program\n";
                                break;
                            }

                            else if (wrongPassCount > 1)
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered is incorrect, you have " << wrongPassCount-- << " tries left\n";
                            }

                            else
                            {
                                cout << "\n\n\t\t\t\t\t\t\t\t\tThe password you entered is incorrect, you have " << wrongPassCount-- << " try left\n";
                            }

                            SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                        }
                    }
                }

                else if (entry == 2)
                {
                    main();
                }
            }
        }

        else
        {
            SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
            cout << "\n\n\t\t\t\t\t\t\t\tYou didnot enter a NIC number, exiting program\n\n"; // 8
            SetConsoleTextAttribute(console.outScreen, console.defaultColor);
        }
    }

    _getch();

    return 0;
}
/* MAIN FUNCTION ENDS HERE */

/* FUNCTION DEFINITIONS START HERE */
int OutputScreen::maximize_outputWindow()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    if (!outScreen || !GetConsoleScreenBufferInfo(outScreen, &info))
    {
        return 80; // Default console width
    }

    return info.dwSize.X;
}

void OutputScreen::display_welcomeMsg()
{
    display_boxes(33); // 33
    display_spaces(3); // 3
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_BLUE);
    cout << "WELCOME TO ADMISSION PORTAL";
    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
    display_spaces(3);
    display_boxes(33);
}

void OutputScreen::display_boxes(int numOfBoxes)
{
    for (int i = 0; i < (console.width - numOfBoxes) / 2; i++)
    {
        cout << (char)BOX;
    }
}

void OutputScreen::display_spaces(int numOfSpaces)
{
    for (int i = 0; i < numOfSpaces; i++)
    {
        cout << " ";
    }
}

void OutputScreen::display_defaultMessages()
{
    system("cls");
    display_boxes(-174); // -174
    cout << endl << endl;
    display_welcomeMsg();
    cout << endl << endl << endl;
}

void OutputScreen::display_loginSuccess()
{
    string success = "Login Successful!";

    SetConsoleTextAttribute(console.outScreen, FOREGROUND_GREEN);
    cout << "\t\t\t\t\t\t\t\t\t      "; // 9

    for (int i = 0; i < success.length(); i++)
    {
        Sleep(40);
        cout << success[i];
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
}

void OutputScreen::display_randomPassSuccess()
{
    string success = "Random Password Matched!";

    SetConsoleTextAttribute(console.outScreen, FOREGROUND_GREEN);
    cout << "\t\t\t\t\t\t\t\t\t      "; // 9

    for (int i = 0; i < success.length(); i++)
    {
        Sleep(40);
        cout << success[i];
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
    Sleep(1000);
}

int get_loginOrSignup()
{
	int entry;
	
    cout << "\t\t\t\t\t\t\tEnter the number of the action that you want to perform\n\n" // 7
		<< "\t\t\t\t\t\t\t1. Login\n"
        << "\t\t\t\t\t\t\t2. Signup\n"
        << "\t\t\t\t\t\t\t3. Forgot Password\n"
        << "\t\t\t\t\t\t\t4. Exit\n\n"
        << "\t\t\t\t\t\t\t-> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    cin >> entry;
	cout << endl;
	
    while (entry != LOGIN && entry != SIGNUP && entry != FORGOT && entry != EXIT)
    {
        SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
        cout << "\t\t\t\t\t\t\tInvalid option, please re-enter\n"; // 7
        SetConsoleTextAttribute(console.outScreen, console.defaultColor);
        cout << "\t\t\t\t\t\t\t-> ";
        SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
        cin >> entry;
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
    
    return entry;
}

string get_NIC()
{
    char nic[16];
    int i = 0;

    cout << "\t\t\t\t\t\t\t\t\tEnter your NIC number\n" // 9
        << "\t\t\t\t\t\t\t\t     -> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    cin.clear();

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
				return "NIC Number Not Entered";
			}
			
			else
			{
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
				cout << "\n\t\t\t\t\t\t\t\t\tInvalid NIC number please re-enter\n"; // 9
                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                cout << "\t\t\t\t\t\t\t\t     -> ";
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
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

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);

    return nic;
}

string get_name()
{
    char name[31];
    int i = 0;

    cout << "\t\t\t\t\t\t\t\t\tEnter Your Name\n" // 9
        << "\t\t\t\t\t\t\t\t     -> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    cin.clear();

    while (true)
    {
        name[i] = _getch();

        if (name[i] == ENTER && i != 0)
        {
            if (i > 30)
            {
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                cout << "\n\t\t\t\t\t\t\t\t\tName Can Only Be Between 1 and 30 Characters\n"; // 9
                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                cout << "\t\t\t\t\t\t\t\t     -> ";
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                i = 0;
            }

            else
            {
                name[i] = '\0';
                break;
            }
        }

        else if (name[i] == BACKSPACE && i > 0)
        {
            --i;
            cout << "\b \b";
        }

        else if ((isalpha(name[i]) || name[i] == ' ' || name[i] == '-') && i <= 30)
        {
            cout << name[i++] << " \b";
        }
    }
    
    SetConsoleTextAttribute(console.outScreen, console.defaultColor);

    return name;
}

string get_pass()
{
    char pass[26];
    int i = 0;

    cout << "\t\t\t\t\t\t\t\t\tEnter Password\n" // 9
        << "\t\t\t\t\t\t\t\t     -> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    cin.clear();

    while (true)
    {
        pass[i] = _getch();

        if (pass[i] == ENTER)
        {
            if (i >= 8 && i <= 24)
            {
                pass[i] = '\0';
                break;
            }
            
            else
            {
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
                cout << "\n\t\t\t\t\t\t\t\t\tPassowrd must be between 8 tou 24 characters\n"; // 9
                SetConsoleTextAttribute(console.outScreen, console.defaultColor);
                cout << "\t\t\t\t\t\t\t\t     -> ";
                SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
                i = 0;
            }
        }

        else if (pass[i] == BACKSPACE && i > 0)
        {
            --i;
            cout << "\b \b";
        }

        else if (isdigit(pass[i]) || isalpha(pass[i]) || ispunct(pass[i]))
        {
            ++i;
            cout << "* \b";
        }
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);

    return pass;
}

char get_type()
{
    char type;

    cout << "\t\t\t\t\t\t\t\t\tAre you an Admin?[Y/N]\n" // 9
        << "\t\t\t\t\t\t\t\t     -> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    cin >> type;
    cout << endl;

    while (type != 'Y' && type != 'y' && type != 'N' && type != 'n')
    {
        SetConsoleTextAttribute(console.outScreen, FOREGROUND_RED);
        cout << "\t\t\t\t\t\t\t\tInvalid option, please re-enter\n"; // 8
        SetConsoleTextAttribute(console.outScreen, console.defaultColor);
        cout << "\t\t\t\t\t\t\t\t-> ";
        SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
        cin >> type;
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);

    return type;
}

long long int check_NIC(string inputNIC)
{
    ifstream in("Users.txt");

    if (!in)
    {
        cout << "File could not open\n";
        exit(1);
    }

    int replace;
    string tempNIC;

    while (getline(in, tempNIC))
    {
        replace = 0;
        for (int i = 1; i < tempNIC.length(); i++)
        {
            if (tempNIC[i] == ',')
            {
                for (int j = i + 1; j < i + 14; j++)
                {
                    if (inputNIC[replace++] != tempNIC[j])
                    {
                        replace = 0;
                        break;
                    }
                }

                if (replace != 0)
                {
                    return in.tellg();
                }

                break;
            }
        }
    }

    in.close();

    return NOTEXISTS;
}

bool check_pass(string inputPass, int index)
{
    ifstream in("Users.txt");

    if (!in)
    {
        cout << "File could not open\n";
        exit(2);
    }

    string tempPass;

    in.seekg(index - inputPass.length() - 2, ios::beg);
    getline(in, tempPass);

    if (inputPass == tempPass)
    {
        return true;
    }

    return false;
}

User create_user(string inputName, string inputNIC, string inputPass)
{
    ofstream out("Users.txt", ios::app);

    if (!out)
    {
        cout << "File could not open\n";
        exit(111);
    }

    User user;
    string success = "Account Created Successfully!";

    user.set_name(inputName);
    user.set_NIC(inputNIC);
    user.set_password(inputPass);

    out << inputName << "," << inputNIC << "," << inputPass << endl;
    out.close();

    cout << "\t\t\t\t\t\t\t\t        "; // 8
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_GREEN);
    
    for (int i = 0; i < success.length(); i++)
    {
        Sleep(40);
        cout << success[i];
    }

    SetConsoleTextAttribute(console.outScreen, console.defaultColor);
    
    return user;
}

void generate_random()
{
    ofstream out("Admin Random.txt");
    
    if (!out)
    {
        cout << "\nFile not opened\n";
        exit(112);
    }

    const char alphanum[] = "012345689ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string generatedString;

    generatedString.reserve(13);

    srand((unsigned)time(NULL) * getpid());
    for (int i = 0; i < 13; i++)
    {
        generatedString += alphanum[rand() & (sizeof(alphanum) - 1)];
    }

    out << generatedString;
    out.close();
}

string get_randomPass()
{
    string temp;

    cout << "\t\t\t\t\t\t\t\t\tEnter The Random Generated Password\n" // 9
        << "\t\t\t\t\t\t\t\t     -> ";
    SetConsoleTextAttribute(console.outScreen, FOREGROUND_INTENSITY);
    getline(cin >> ws, temp);
    SetConsoleTextAttribute(console.outScreen, console.defaultColor);

    return temp;
}

bool confirm_generatedPass(string temp)
{
    ifstream in("Admin Random.txt");

    if (!in)
    {
        cout << "\nFile not opened\n";
        exit(3);
    }

    string checkString;

    getline(in, checkString);

    if (temp == checkString)
    {
        return true;
    }

    return false;
}
/* FUNCTION DEFINITIONS END HERE */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int selectArray()
{
    srand(time(NULL));
    int i = rand() % 5;
    if (i == 0)
        i++;
    return i;
}

int getKey()
{
    srand(time(NULL));
    int key = rand() % 26;
    return key;
}

string generate_password(int length)
{
    string password = "";
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string s_symbol = "!@#$%&";
    string number = "0123456789";

    // initializing local variables
    int key, count_alphabet = 0, count_ALPHABET = 0, count_number = 0, count_s_symbol = 0;
    int count = 0;
    while (count < length)
    {

        int k = selectArray();
        if (count == 0)
        {
            k = k % 3;
            if (k == 0)
            {
                k++;
            }
        }

        switch (k)
        {
        case 1:
            if ((count_alphabet == 2) && (count_number == 0 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_s_symbol == 0))
                break;

            key = getKey();
            password = password + alphabet[key];
            count_alphabet++;
            count++;
            break;

        case 2:

            if ((count_ALPHABET == 2) && (count_number == 0 || count_alphabet == 0 || count_alphabet == 1 || count_s_symbol == 0))
                break;
            key = getKey();
            password = password + ALPHABET[key];
            count_ALPHABET++;
            count++;
            break;

        case 3:
            if ((count_number == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 1 || count_ALPHABET == 0 || count_s_symbol == 0))
                break;

            key = getKey();
            key = key % 10;
            password = password + number[key];
            count_number++;
            count++;
            break;

        case 4:
            if ((count_s_symbol == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_number == 0))
                break;

            key = getKey();
            key = key % 6;
            password = password + s_symbol[key];
            count_s_symbol++;
            count++;
            break;
        }
    }

    return password;
}

void printStrongNess(const string &input)       //saymun's code
{
    int n = input.length();

    // Checking lower alphabet in string
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;
    string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

    for (int i = 0; i < n; i++)
    {
        if (islower(input[i]))
            hasLower = true;
        if (isupper(input[i]))
            hasUpper = true;
        if (isdigit(input[i]))
            hasDigit = true;

        size_t special = input.find_first_not_of(normalChars);
        if (special != string::npos)
            specialChar = true;
    }

    // Strength of password
    cout << "Strength of password: ";
    if (hasLower && hasUpper && hasDigit &&
        specialChar && (n >= 8))
        cout << "Strong" << endl;
    else if ((hasLower || hasUpper) &&
             specialChar && (n >= 6))
        cout << "Moderate" << endl;
    else
        cout << "Weak\n\nYou have to change your password." << endl;
}

void writePasswordsToFile(int length, int numPasswords , string username[])
{
    ofstream outputFile("passwords.txt", ios::app);
    time_t currentTime = time(nullptr);
    struct tm* localTime = localtime(&currentTime);
    char dateTime[100];
    strftime(dateTime, 100, "%Y-%m-%d %H:%M:%S", localTime);

    if (!outputFile)
    {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    for (int i = 0; i < numPasswords; ++i)
    {
        string password = generate_password(length);
        outputFile <<"Username: "<<username[i] <<",  Password: "<< password << ",  Creation Time:  "<<dateTime <<endl;
    }

    outputFile.close();
    cout << "Generated passwords are stored in 'passwords.txt'." << endl;
}

int main()
{   
     srand(time(NULL));
    int opt, length, numPasswords;
    string input,username[100];
    // Menu

    ofstream outputFile("passwords.txt", ios::app);
    if (!outputFile)
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }


    do
    {
        cout << "\n-------------------------------\n";
        cout << " Password Generator and Checker\n";
        cout << "-------------------------------\n\n";
        cout << "    1. Generate Passwords"
             << "\n";
        cout << "    2. Checking Passwords"
             << "\n";
        cout << "    0. Exit"
             << "\n\n";
        cout << "Press key 1 to Generate Passwords, key 2 to Checking Passwords, and key 0 to Exit: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
            cout << "Enter Length of each password: ";
            cin >> length;
            cout << "Enter number of passwords to generate: ";
            cin >> numPasswords;
            if (length < 8)
            {
                cout << "\nError: Password Length Should be at least 8\n";
                break;
            }
            else if (length > 100)
            {
                cout << "\nError: Maximum length of password should be 100\n";
                break;
            }

            
            for(int i =0;i<numPasswords;i++)
            {   
                cout<<"Enter your username: ";
                cin>>username[i];
            }
            writePasswordsToFile(length, numPasswords,username);
            break;

        case 2:
            cout << "Enter a password to check: ";
            cin.ignore();
            getline(cin, input);
            printStrongNess(input);
            break;

        default:
            if (opt != 0)
            {
                cout << "\nInvalid choice\n";
                cout << "Please Press (1) to generate passwords, (2) to check passwords, and (0) to Exit\n";
            }
            break;
        }
    } while (opt != 0);

    return 0;
}

#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

const string ClientsFileName = "Clients.txt";

struct stClient
{
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter account number: ";
    cin >> AccountNumber;

    return AccountNumber;
}

string ReadPIN()
{
    string PIN = "";

    cout << "Enter PIN: ";
    cin >> PIN;

    return PIN;
}

bool IsAccountNumberExisted(string AccountNumber, vector <stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
            return true;
    }
    return false;
}

vector <string> SplitString(string Sentence, string Delim = " ")
{
    vector <string> vWord;

    size_t Pos = 0; // The position of Delim
    string Word = ""; // Empty string

    while ((Pos = Sentence.find(Delim)) != string::npos)
    {
        Word = Sentence.substr(0, Pos); // Stor word

        if (Word != "")
            vWord.push_back(Word);

        Sentence.erase(0, Pos + Delim.length()); // Delet printed word from string
    }

    if (Sentence != "")
        vWord.push_back(Sentence);

    return vWord;
}

stClient ConvertLineToRecord(string Line, string Separator = "#//#")
{
    stClient C;
    vector <string> vClientData = SplitString(Line, Separator);

    C.AccountNumber = vClientData[0];
    C.PINCode = vClientData[1];
    C.Name = vClientData[2];
    C.Phone = vClientData[3];
    C.AccountBalance = stod(vClientData[4]);

    return C;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
    vector <stClient> vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";

        while (getline(MyFile, Line))
        {
            stClient C = ConvertLineToRecord(Line);
            vClient.push_back(C);
        }

        MyFile.close();
    }

    return vClient;
}

bool IsTruePIN(string PIN, string AccountNumber, vector <stClient>& vClient)
{
    for (stClient& ClientData : vClient)
    {
        if (ClientData.AccountNumber == AccountNumber)
        {
            if (ClientData.PINCode == PIN)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

short Read_ATM_MenuChoose()
{
    short UserChoose = 0;

    cout << "Choose what do you want to do (1 To 5): ";
    cin >> UserChoose;

    while (UserChoose < 1 || UserChoose > 5)
    {
        cout << "\nInvaild Choose, Please try again: ";
        cin >> UserChoose;
    }

    return UserChoose;
}

enum en_ATM_MenuOptions
{
    etQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3, 
    eCheckBalance = 4,
    Logout = 5
};

string GlobalClientAccountNumber = "";

enum enQuickWithdrawOptions
{
    e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5,
    e600 = 6, e800 = 7, e1000 = 8, eExit = 9
};

short enumChooseToAmount(enQuickWithdrawOptions Choose)
{
    switch (Choose)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 400;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    case 9: return -1;
    default: return 0;
    }
}

string ConvertClientRecordToLine(stClient& C, string Separator = "#//#")
{
    string ClientRecord = "";

    ClientRecord = C.AccountNumber + Separator;
    ClientRecord += C.PINCode + Separator;
    ClientRecord += C.Name + Separator;
    ClientRecord += C.Phone + Separator;
    ClientRecord += to_string(C.AccountBalance);

    return ClientRecord;
}

bool SaveClientDataToFile(string FileName, vector <stClient>& vClient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClient& C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                string Line = ConvertClientRecordToLine(C);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
        return true;
    }

    return false;
}

void Show_ATM_MainMenuScreen();

void GoToBackTo_ATM_MainMenuScreen()
{
    cout << "\n\nPress any key to go to main Menu.....";
    system("pause>0");
    system("cls");
    Show_ATM_MainMenuScreen();
}

void Login();

void QuickWithdraw(enQuickWithdrawOptions Choose)
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    short WithdrawAmount = enumChooseToAmount(Choose);

    if (WithdrawAmount == -1) // Logout
    {
        system("cls");
        Login();
    }

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == GlobalClientAccountNumber)
        {
            char Sure = 'N';

            cout << "\nYou are about to Withdraw " << WithdrawAmount
                << " Pound, Do you want to continue [Y|N]: ";
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                Client.AccountBalance -= WithdrawAmount;
                SaveClientDataToFile(ClientsFileName, vClient);

                cout << "\nWithdraw done Successfully." << endl;
                cout << "Account balance is: " << Client.AccountBalance << endl;
            }
        }
    }
}

short ReadQuickWithdrawAmountOption()
{
    short OptionNumber = 0;
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == GlobalClientAccountNumber)
        {
            cout << "Your balance is " << Client.AccountBalance << endl;
        }
    }

    cout << "Choose the amount do you want to Withdraw [1 To 8]: ";
    cin >> OptionNumber;

    while (OptionNumber < 1 || OptionNumber > 9) // [9] Exit
    {
        cout << "Invaild choose, please choose one of the above options: ";
        cin >> OptionNumber;
    }

    return OptionNumber;
}

void ShowtQuickWithdrawScreen()
{
    system("cls");
    cout << "======================================================" << endl;
    cout << "\t\tQuick Withdraw" << endl;
    cout << "======================================================" << endl;
    cout << "\t[1] 20\t\t[2] 50" << endl;
    cout << "\t[3] 100\t\t[4] 200" << endl;
    cout << "\t[5] 400\t\t[6] 600" << endl;
    cout << "\t[7] 800\t\t[8] 1000" << endl;
    cout << "\t[9] Exit" << endl;
    cout << "======================================================" << endl;
    QuickWithdraw((enQuickWithdrawOptions)ReadQuickWithdrawAmountOption());
}

int ReadNormalWithdrawAmount()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    int Amount = 0;

    cout << "Enter an amount that is multiple of 5: ";
    cin >> Amount;

    for (stClient& ClientData: vClient)
    {
        if (ClientData.AccountNumber == GlobalClientAccountNumber)
        {
            cout << "\nYour balance is " << ClientData.AccountBalance << endl;

            while (Amount < 1 || Amount > ClientData.AccountBalance ||
                Amount % 5 != 0)
            {
                if (Amount > ClientData.AccountBalance)
                {
                    cout << "The amount you entered is greater than your balance." << endl;
                }

                cout << "\nEnter an amount that is multiple of 5: ";
                cin >> Amount;
            }
        }
    }
    
    return Amount;
}

void NormalWithdraw()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    int Amount = ReadNormalWithdrawAmount();

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == GlobalClientAccountNumber)
        {
            char Sure = 'N';

            cout << "You are about to Withdraw " << Amount
                << " Pound, Do you want to continue [Y|N]: ";
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                Client.AccountBalance -= Amount;
                SaveClientDataToFile(ClientsFileName, vClient);

                cout << "\nWithdraw done Successfully." << endl;
                cout << "Account balance is: " << Client.AccountBalance << endl;
            }
        }
    }
}

void ShowNormalWithdrawScreen()
{
    cout << "======================================================" << endl;
    cout << "\t\tNormal Withdraw Screen" << endl;
    cout << "======================================================" << endl;
    NormalWithdraw();
}

int ReadDepositAmount()
{
    int Amount = 0;

    cout << "Enter an amount that is multiple of 5: ";
    cin >> Amount;

    while (Amount < 1)
    {
        cout << "Invaild amount, Please enter an amount is greater than 1: ";
        cin >> Amount;
    }

    return Amount;
}

void DepositToClient()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    int DepositAmount = 0;
    char Sure = 'n';

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == GlobalClientAccountNumber)
        {
            DepositAmount = ReadDepositAmount();

            cout << "\nAre you sure you want to perform this transaction? [Y|N]" << endl;
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                Client.AccountBalance += DepositAmount;
                SaveClientDataToFile(ClientsFileName, vClient);

                cout << "\nDiposit done Successfully." << endl;
                cout << "Account balance is: " << Client.AccountBalance << endl;
            }
        }
    }
}

void ShowDepositScreen()
{
    cout << "======================================================" << endl;
    cout << "\t\tDeposit Screen" << endl;
    cout << "======================================================" << endl;
    DepositToClient();
}

void ShowCheckBalanceScreen()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    cout << "======================================================" << endl;
    cout << "\t\Deposit Screen" << endl;
    cout << "======================================================" << endl;

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == GlobalClientAccountNumber)
        {
            cout << "Your balance is " << Client.AccountBalance << endl;
        }
    }
}

void Perform_ATM_MenuChoose(en_ATM_MenuOptions UserChoose)
{
    switch (UserChoose)
    {
    case 1: // Quick Withdraw
    {
        system("cls");
        ShowtQuickWithdrawScreen();
        GoToBackTo_ATM_MainMenuScreen();
        break;
    }
    case 2: // Normal Withdraw
    {
        system("cls");
        ShowNormalWithdrawScreen();
        GoToBackTo_ATM_MainMenuScreen();
        break;
    }
    case 3: // Deposit
    {
        system("cls");
        ShowDepositScreen();
        GoToBackTo_ATM_MainMenuScreen();
        break;
    }
    case 4: // Check Balance
    {
        system("cls");
        ShowCheckBalanceScreen();
        GoToBackTo_ATM_MainMenuScreen();
        break;
    }
    case 5: // Logout
    {
        system("cls");
        Login();
        break;
    }
    default:
    {
        cout << "\nWe are sorry, An error occured." << endl;
    }
    }
}

void Show_ATM_MainMenuScreen()
{
    system("cls");
    cout << "======================================================" << endl;
    cout << "\t\tATM Main Menu Screen" << endl;
    cout << "======================================================" << endl;
    cout << "[1] Quick Withdraw." << endl;
    cout << "[2] Normal Withdraw." << endl;
    cout << "[3] Deposit." << endl;
    cout << "[4] Check Balance." << endl;
    cout << "[5] Logout." << endl;
    cout << "======================================================" << endl;
    Perform_ATM_MenuChoose((en_ATM_MenuOptions)Read_ATM_MenuChoose());
}

bool IsTrue_PIN_AndAccountNumber()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    GlobalClientAccountNumber = ReadClientAccountNumber();
    string PIN = ReadPIN();
    short AttemptsCounter = 0;

    while (!IsAccountNumberExisted(GlobalClientAccountNumber, vClient) ||
        !IsTruePIN(PIN, GlobalClientAccountNumber, vClient))
    {
        system("cls");
        cout << "======================================================" << endl;
        cout << "\t\tLogin Screen" << endl;
        cout << "======================================================" << endl;
        cout << "Invaild Account number/ PIN code.\n" << endl;

        GlobalClientAccountNumber = ReadClientAccountNumber();
        PIN = ReadPIN();

        AttemptsCounter++;

        if (AttemptsCounter == 5)
        {
            cout << "\n\nYou have exceeded the number of login attempts." << endl;
            return false;
        }
    }

    return true;
}

void Login()
{
    system("cls");
    cout << "======================================================" << endl;
    cout << "\t\tLogin Screen" << endl;
    cout << "======================================================" << endl;
    
    if (IsTrue_PIN_AndAccountNumber())
        Show_ATM_MainMenuScreen();
    else
        return;
}

int main()
{
    Login();
    return 0;
}
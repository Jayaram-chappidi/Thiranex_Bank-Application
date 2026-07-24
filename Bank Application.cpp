#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Deposit: ";
        cin >> balance;
    }

    void displayAccount()
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << name;
        cout << "\nBalance        : Rs. " << balance;
        cout << "\n-----------------------------";
    }
};

// Create New Account
void createNewAccount()
{
    Account account;

    ofstream file("accounts.dat", ios::binary | ios::app);

    account.createAccount();

    file.write((char*)&account, sizeof(account));

    file.close();

    cout << "\nAccount created successfully!\n";
}

// Display Account Balance
void checkBalance()
{
    int accountNumber;
    Account account;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    ifstream file("accounts.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.accountNumber == accountNumber)
        {
            cout << "\nAccount Details:";
            account.displayAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount not found!\n";
    }
}

// Deposit Money
void depositMoney()
{
    int accountNumber;
    double amount;
    Account account;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    fstream file("accounts.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.accountNumber == accountNumber)
        {
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            if (amount > 0)
            {
                account.balance += amount;

                file.seekp(-static_cast<int>(sizeof(account)), ios::cur);
                file.write((char*)&account, sizeof(account));

                cout << "\nAmount deposited successfully!\n";
                cout << "Updated Balance: Rs. " << account.balance;

                found = true;
            }
            else
            {
                cout << "\nInvalid amount!\n";
            }

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount not found!\n";
    }
}

// Withdraw Money
void withdrawMoney()
{
    int accountNumber;
    double amount;
    Account account;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    fstream file("accounts.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.accountNumber == accountNumber)
        {
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount <= 0)
            {
                cout << "\nInvalid amount!\n";
            }
            else if (amount > account.balance)
            {
                cout << "\nInsufficient balance!\n";
            }
            else
            {
                account.balance -= amount;

                file.seekp(-static_cast<int>(sizeof(account)), ios::cur);
                file.write((char*)&account, sizeof(account));

                cout << "\nAmount withdrawn successfully!\n";
                cout << "Updated Balance: Rs. " << account.balance;

                found = true;
            }

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount not found!\n";
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n\n========== BANK MANAGEMENT SYSTEM ==========";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            cout << "\nThank you for using the Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
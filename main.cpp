#include <iostream>
#include <vector>
#include <string>
#include "class.h"
using namespace std;

void menu1();
void menu2();
int main()
{
    ATM atm;
    atm.addAccount(new Account("10000000","0007",5000));
    atm.addAccount(new Account("12345678","1234",1000));
    atm.addAccount(new Account("1000","1111",1000));
    atm.addAccount(new SavingsAccount("10000001","1111",1500,5));
    atm.addAccount(new KidsAccount("10000002","1111",1600,500));

    int opt1=0,opt2=0,amount;
    string accountNumber,pin;
    do
    {
        menu1();
        cout << "Option: ";
        cin >> opt1;
        switch(opt1)
        {
            case 1:
            {
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter pin: ";
                cin >> pin;
                if(atm.login(accountNumber,pin))
                {
                    cout << endl << "Login successful!" << endl << endl;
                    atm.selectAccount(accountNumber);
                    do
                    {
                        menu2();
                        cout << "Option: ";
                        cin >> opt2;
                        switch(opt2)
                        {
                            case 1:
                                cout << "Amount: ";
                                cin >> amount;
                                if(atm.deposit(amount)) {
                                    cout << endl << "Deposit successful!" << endl;
                                }
                                else
                                    cout << endl << "Invalid amount" << endl;
                                break;
                            case 2:
                                cout << "Amount: ";
                                cin >> amount;
                                if(atm.withdraw(amount)) {
                                    cout << endl << "Withdrawal successful!" << endl;
                                }
                                else
                                    cout << endl << "Invalid amount or insufficient funds" << endl;
                                break;
                            case 3:
                                cout << endl << atm.getBalance() << " RON" << endl;
                                break;
                            case 4:
                                atm.details();
                                break;
                            case 5:
                                cout << endl << "Card removed" << endl;
                                break;
                            default:
                                cout << "Invalid option" << endl;
                                break;
                        }
                        cout << endl;
                    }while(opt2 != 5);
                }
                else
                    cout << endl << "Login failed!" << endl << endl;
                break;
            }
            case 2:
                break;
            default:
                cout << "Invalid option" << endl << endl;
                break;
        }
    }while(opt1 != 2);
    return 0;
}
void menu2()
{
    cout << "<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Balance" << endl;
    cout << "4. Card information" << endl;
    cout << "5. Exit" << endl;
}
void menu1()
{
    cout << "<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "1. Insert card" << endl;
    cout << "2. Exit" << endl;
}

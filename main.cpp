#include <iostream>
#include <vector>
using namespace std;

class Account {
private:
    string accountNumber;
    string pin;
    double balance;
public:
    //Account(const string &accountNumber, const string &pin, double balance) : accountNumber(accountNumber), pin(pin), balance(balance) {}
    Account(const string& accountNumber, const string& pin,const double& balance)
    {
        this->accountNumber = accountNumber;
        this->pin = pin;
        this->balance = balance;
    }
    Account(const Account& aux)
    {
        this->accountNumber = aux.accountNumber;
        this->pin = aux.pin;
        this->balance = aux.balance;
    }
    Account& operator=(Account& aux)
    {
        if (this == &aux) {
            return *this;
        }
        this->accountNumber = aux.accountNumber;
        this->pin = aux.pin;
        this->balance = aux.balance;
        return *this;
    }
    bool checkPin(const string& enteredPin) {
        return (enteredPin == pin);
    }
    double getBalance() const{
        return balance;
    }
    void addMoney(const double& amount) {
        balance += amount;
    }
    string getNumber(){
        return accountNumber;
    }
    friend ostream& operator<<(ostream& out, const Account &aux)
    {
        out << aux.balance;
        return out;
    }
    ~Account() = default;
};

class ATM {
private:
    vector<Account> accounts;
    Account *currentAccount = nullptr;
public:
    void addAccount(const Account& acc) {
        accounts.push_back(acc);
    }
    bool login(const string& accNr,const string& pin)
    {
        for(auto acc: accounts)
        {
            if(acc.getNumber() == accNr && acc.checkPin(pin))
                return true;
        }
        return false;
    }
    void selectAccount(const string& accNr)
    {
        for(Account &acc: accounts)
        {
            if(acc.getNumber() == accNr){
                currentAccount = &acc;
                break;
            }
        }
    }
    double getBalance() {
        return currentAccount->getBalance();
    }
    void getBalance2() {
        cout << *currentAccount << endl;
    }
    void changeMoney(int amount)
    {
        currentAccount->addMoney(amount);
    }
    ~ATM() = default;
};
void menu1();
void menu2();
int main()
{
    ATM atm;
    atm.addAccount(Account("777","1234",1000));

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
                                if(amount > 0)
                                {
                                    atm.changeMoney(amount);
                                    cout << endl << "Deposit successful!" << endl;
                                }
                                else
                                    cout << endl << "Invalid amount" << endl;
                                break;
                            case 2:
                                cout << "Amount: ";
                                cin >> amount;
                                if(amount > 0 && atm.getBalance() >= amount)
                                {
                                    atm.changeMoney(-amount);
                                    cout << endl << "Withdrawal successful!" << endl;
                                }
                                else
                                    cout << endl << "Invalid amount or insufficient funds" << endl;
                                break;
                            case 3:
                                cout << endl << atm.getBalance() << " RON" << endl;
                                //atm.getBalance2();
                                break;
                            case 4:
                                break;
                            default:
                                cout << "Invalid option" << endl;
                                break;
                        }
                        cout << endl;
                    }while(opt2 != 4);
                }
                else
                    cout << endl << "Login failed!" << endl << endl;
                break;
            }
            case 2:
                break;
            default:
                cout << "Invalid option" << endl;
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
    cout << "4. Exit" << endl;
}
void menu1()
{
    cout << "<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "1. Insert card" << endl;
    cout << "2. Exit" << endl;
}

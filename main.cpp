#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
protected:
    string accountNumber;
    string pin;
    double balance;
public:
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
    virtual void details() const
    {
        cout << "Account." << endl;
    };
    friend ostream& operator<<(ostream& out, const Account &aux)
    {
        out << aux.balance;
        return out;
    }
    friend istream& operator>>(istream& in, Account &aux)
    {
        in >> aux.accountNumber;
        return in;
    }
    virtual ~Account() = default;
};

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(const string& accountNumber, const string& pin, const double& balance, const double& interest) : Account(accountNumber,pin,balance), interestRate(interest) {}
    SavingsAccount(const SavingsAccount& aux) : Account(aux)
    {
        this->interestRate = aux.interestRate;
    }
//    void addInterest() {
//        balance += balance * (interestRate / 100);
//    }
    void details() const override
    {
        cout << "Savings account." << endl;
        cout << "Interest rate: " << interestRate << "%" << endl;
    };
    ~SavingsAccount() override = default;
};
class KidsAccount : public Account {
private:
    double withdrawLimit;
    double withdrawCnt = 0;
public:
    KidsAccount(const string& accountNumber, const string& pin, const double& balance, const double& limit) : Account(accountNumber,pin,balance), withdrawLimit(limit) {}
    KidsAccount(const KidsAccount& aux) : Account(aux)
    {
        this->withdrawLimit = aux.withdrawLimit;
    }
    void details() const override
    {
        cout << "Child account." << endl;
        cout << "Withdraw limit: " << withdrawLimit << " RON" << endl;
    };
//    void resetLimit(){
//        withdrawCnt = 0;
//    }
    double withdrawLeft() const{
        return withdrawLimit-withdrawCnt;
    }
    void cntIncrease(const double& n){
        withdrawCnt+=n;
    }
    ~KidsAccount() override = default;
};

class ATM {
private:
    vector<Account*> accounts;
    Account *currentAccount = nullptr;
public:
    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }
    bool login(const string& accNr,const string& pin)
    {
        for(auto acc: accounts)
        {
            if(acc->getNumber() == accNr && acc->checkPin(pin))
                return true;
        }
        return false;
    }
    void selectAccount(const string& accNr)
    {
        for(auto acc: accounts)
        {
            if(acc->getNumber() == accNr){
                currentAccount = acc;
                break;
            }
        }
    }
    double getBalance() {
        return currentAccount->getBalance();
    }
    bool deposit(const int& amount)
    {
        if(amount > 0)
        {
            currentAccount->addMoney(amount);
            return true;
        }
        else
            return false;
    }
    bool withdraw(const int& amount)
    {
        if(typeid(*currentAccount) == typeid(KidsAccount))
        {
            KidsAccount *p = dynamic_cast<KidsAccount*>(currentAccount);
            if(amount > 0 && p->getBalance() >= amount && amount <= p->withdrawLeft())
            {
                p->addMoney(-amount);
                p->cntIncrease(amount);
                return true;
            }
            else
            {
                if(amount > p->withdrawLeft())
                    cout << "Limit reached!" << endl;
                return false;
            }

        }
        if(amount > 0 && currentAccount->getBalance() >= amount)
        {
            currentAccount->addMoney(-amount);
            return true;
        }
        else
            return false;
    }
    void details() const{
        currentAccount->details();
    }
    ~ATM() = default;
};
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

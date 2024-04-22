#ifndef OOP_CLASS_H
#define OOP_CLASS_H

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
    Account(const string& accountNumber, const string& pin,const double& balance);
    Account(const Account& aux);
    Account& operator=(Account& aux);
    bool checkPin(const string& enteredPin);
    double getBalance() const;
    void addMoney(const double& amount);
    string getNumber();
    virtual void details() const;
    friend ostream& operator<<(ostream& out, const Account &aux);
    friend istream& operator>>(istream& in, Account &aux);
    virtual ~Account() = default;
};

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(const string& accountNumber, const string& pin, const double& balance, const double& interest);
    SavingsAccount(const SavingsAccount& aux);
    void details() const override;
    ~SavingsAccount() = default;
};

class KidsAccount : public Account {
private:
    double withdrawLimit;
    double withdrawCnt = 0;
public:
    KidsAccount(const string& accountNumber, const string& pin, const double& balance, const double& limit);
    KidsAccount(const KidsAccount& aux);
    void details() const override;
    void resetLimit();
    double withdrawLeft() const;
    void cntIncrease(const double& n);
    ~KidsAccount() = default;
};

class ATM {
private:
    vector<Account*> accounts;
    Account *currentAccount = nullptr;
public:
    void addAccount(Account* acc);
    bool login(const string& accNr,const string& pin);
    void selectAccount(const string& accNr);
    double getBalance();
    bool deposit(const int& amount);
    bool withdraw(const int& amount);
    void details() const;
    ~ATM() = default;
};

#endif //OOP_CLASS_H

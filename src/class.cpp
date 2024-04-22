#include "class.h"

Account::Account(const string& accountNumber, const string& pin,const double& balance)
{
    this->accountNumber = accountNumber;
    this->pin = pin;
    this->balance = balance;
}
Account::Account(const Account& aux)
{
    this->accountNumber = aux.accountNumber;
    this->pin = aux.pin;
    this->balance = aux.balance;
}
Account& Account::operator=(Account& aux)
{
    if (this == &aux)
    {
        return *this;
    }
    this->accountNumber = aux.accountNumber;
    this->pin = aux.pin;
    this->balance = aux.balance;
    return *this;
}
bool Account::checkPin(const string& enteredPin)
{
    return (enteredPin == pin);
}
double Account::getBalance() const
{
    return balance;
}
void Account::addMoney(const double& amount)
{
    balance += amount;
}
string Account::getNumber()
{
    return accountNumber;
}
void Account::details() const
{
    cout << "Account." << endl;
};
ostream& operator<<(ostream& out, const Account &aux)
{
    out << aux.balance;
    return out;
}
istream& operator>>(istream& in, Account &aux)
{
    in >> aux.accountNumber;
    return in;
}

// SAVINGS ACCOUNT

SavingsAccount::SavingsAccount(const string& accountNumber, const string& pin, const double& balance, const double& interest) : Account(accountNumber,pin,balance), interestRate(interest) {}
SavingsAccount::SavingsAccount(const SavingsAccount& aux) : Account(aux)
{
    this->interestRate = aux.interestRate;
}
//void SavingsAccount::addInterest()
//{
//    balance += balance * (interestRate / 100);
//}
void SavingsAccount::details() const
{
    cout << "Savings account." << endl;
    cout << "Interest rate: " << interestRate << "%" << endl;
};

// KIDS ACCOUNT

KidsAccount::KidsAccount(const string& accountNumber, const string& pin, const double& balance, const double& limit) : Account(accountNumber,pin,balance), withdrawLimit(limit) {}
KidsAccount::KidsAccount(const KidsAccount& aux) : Account(aux)
{
    this->withdrawLimit = aux.withdrawLimit;
}
void KidsAccount::details() const
{
    cout << "Child account." << endl;
    cout << "Withdraw limit: " << withdrawLimit << " RON" << endl;
};
void KidsAccount::resetLimit()
{
    withdrawCnt = 0;
}
double KidsAccount::withdrawLeft() const
{
    return withdrawLimit-withdrawCnt;
}
void KidsAccount::cntIncrease(const double& n)
{
    withdrawCnt+=n;
}

// ATM

void ATM::addAccount(Account* acc)
{
    accounts.push_back(acc);
}
bool ATM::login(const string& accNr,const string& pin)
{
    for(auto acc: accounts)
    {
        if(acc->getNumber() == accNr && acc->checkPin(pin))
            return true;
    }
    return false;
}
void ATM::selectAccount(const string& accNr)
{
    for(auto acc: accounts)
    {
        if(acc->getNumber() == accNr)
        {
            currentAccount = acc;
            break;
        }
    }
}
double ATM::getBalance()
{
    return currentAccount->getBalance();
}
bool ATM::deposit(const int& amount)
{
    if(amount > 0)
    {
        currentAccount->addMoney(amount);
        return true;
    }
    else
        return false;
}
bool ATM::withdraw(const int& amount)
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
void ATM::details() const
{
    currentAccount->details();
}

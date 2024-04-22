#include <gtest/gtest.h>
#include "example.h"
#include "class.h"

TEST(SuiteName, acc) {
    Account acc("1234", "1234", 2000);
    Account x(acc);
    EXPECT_EQ(x.getNumber(), "1234");
    EXPECT_EQ(acc.getNumber(), "1234");
    EXPECT_EQ(acc.getBalance(), 2000);
    EXPECT_EQ(acc.checkPin("1234"), true);
    acc.addMoney(500);
    EXPECT_EQ(acc.getBalance(), 2500);
}

TEST(SuiteName, savingsacc) {
    SavingsAccount acc("1234", "1234", 1000, 5);
    EXPECT_EQ(acc.getNumber(), "1234");
    EXPECT_EQ(acc.getBalance(), 1000);
}

TEST(SuiteName, kidsacc) {
    KidsAccount acc("1234", "1234", 2000, 500);
    EXPECT_EQ(acc.getNumber(), "1234");
    EXPECT_EQ(acc.getBalance(), 2000);
    EXPECT_EQ(acc.withdrawLeft(), 500);
    acc.cntIncrease(250);
    EXPECT_EQ(acc.withdrawLeft(), 250);
}

TEST(SuiteName, atmtest){
    ATM atm;
    atm.addAccount(new Account("1234", "1111", 2000));
    EXPECT_EQ(atm.login("1234","1111"), true);
    atm.selectAccount("1234");
    EXPECT_EQ(atm.getBalance(), 2000);
    atm.deposit(500);
    EXPECT_EQ(atm.getBalance(), 2500);
    atm.withdraw(600);
    EXPECT_EQ(atm.getBalance(), 1900);
}

TEST(SuiteName, TestName) {
    EXPECT_EQ(doSomething(10), 10);
    // Other assertions: https://google.github.io/googletest/reference/assertions.html#boolean
}

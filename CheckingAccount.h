#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    // Constructor calls base class constructor
    CheckingAccount(std::string accNum, std::string holder, double bal, double fee);

    // Override Withdraw to include transaction fee
    bool Withdraw(double amount) override;
};

#endif

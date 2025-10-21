#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H



#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"


class BankAccount {
public:

    void printHistory() const;

    // Constructors
    BankAccount();
    BankAccount(std::string accNum, std::string holder, double bal);

    // Rule of Three
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount();

    bool Deposit(double amount);
    virtual bool Withdraw(double amount);

    // Operators
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    // Getters and one setter
    std::string GetAccountNumber() const;
    std::string GetAccountHolderName() const;
    double GetBalance() const;
    void SetAccountHolderName(const std::string& newName);


    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();

private:

    std::vector<Transaction> transactionHistory;
    void logTransaction(const std::string& type, double amount);

    char* accountNumber;
    char* accountHolderName;
    double balance;

    static char* allocCopy(const std::string& s);
};

#endif

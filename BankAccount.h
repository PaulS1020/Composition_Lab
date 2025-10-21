#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <iostream>

class BankAccount {
public:
    // Constructors
    BankAccount();
    BankAccount(std::string accNum, std::string holder, double bal);

    // Rule of Three
    BankAccount(const BankAccount& other);            // copy constructor
    BankAccount& operator=(const BankAccount& other); // copy assignment
    virtual ~BankAccount();                                   // destructor

    bool Deposit(double amount);
    virtual bool Withdraw(double amount);

    // Operators
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);     // withdraw in place
    bool operator==(const BankAccount& other) const; // same account number
    bool operator<(const BankAccount& other) const;  // compare balances
    bool operator>(const BankAccount& other) const;

    // Getters and one setter
    std::string GetAccountNumber() const;
    std::string GetAccountHolderName() const;
    double GetBalance() const;
    void SetAccountHolderName(const std::string& newName);

    // Static helpers
    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();

private:
    // Use simple dynamic memory so we must manage it
    char* accountNumber;
    char* accountHolderName;
    double balance;

    static char* allocCopy(const std::string& s);
};

#endif

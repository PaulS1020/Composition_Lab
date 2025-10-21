#include "BankAccount.h"
#include <cstring>
#include <limits>

// Make a new char array and copy the string into it
char* BankAccount::allocCopy(const std::string& s) {
    char* p = new char[s.size() + 1];
    std::memcpy(p, s.c_str(), s.size() + 1);
    return p;
}

// Default values
BankAccount::BankAccount() {
    accountNumber = allocCopy("0000");
    accountHolderName = allocCopy("Unknown");
    balance = 0.0;
}

BankAccount::BankAccount(std::string accNum, std::string holder, double bal) {
    accountNumber = allocCopy(accNum);
    accountHolderName = allocCopy(holder);
    if (bal >= 0.0) balance = bal;
    else balance = 0.0;
}

BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = allocCopy(other.GetAccountNumber());
    accountHolderName = allocCopy(other.GetAccountHolderName());
    balance = other.balance;
}

// Copy assignment
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        char* newNum = allocCopy(other.GetAccountNumber());
        char* newName = allocCopy(other.GetAccountHolderName());
        delete[] accountNumber;
        delete[] accountHolderName;
        accountNumber = newNum;
        accountHolderName = newName;
        balance = other.balance;
    }
    return *this;
}

// Destructor
BankAccount::~BankAccount() {
    delete[] accountNumber;
    delete[] accountHolderName;
}

// Put money in
bool BankAccount::Deposit(double amount) {
    if (amount <= 0.0) return false;
    balance += amount;
    return true;
}

// Take money out
bool BankAccount::Withdraw(double amount) {
    if (amount <= 0.0) return false;
    if (amount > balance) return false;
    balance -= amount;
    return true;
}

// Operators required by the lab
BankAccount& BankAccount::operator+=(double amount) {
    Deposit(amount);
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    Withdraw(amount);
    return *this;
}

bool BankAccount::operator==(const BankAccount& other) const {
    return GetAccountNumber() == other.GetAccountNumber();
}

bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

// Getters and setter
std::string BankAccount::GetAccountNumber() const {
    return std::string(accountNumber);
}

std::string BankAccount::GetAccountHolderName() const {
    return std::string(accountHolderName);
}

double BankAccount::GetBalance() const {
    return balance;
}

void BankAccount::SetAccountHolderName(const std::string& newName) {
    char* tmp = allocCopy(newName);
    delete[] accountHolderName;
    accountHolderName = tmp;
}

// Static helpers
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "Account Number: " << account.GetAccountNumber() << "\n";
    std::cout << "Holder Name:    " << account.GetAccountHolderName() << "\n";
    std::cout << "Balance:        $" << account.GetBalance() << "\n";
}

BankAccount BankAccount::createAccountFromInput() {
    std::string accNum;
    std::string holder;
    double initial = 0.0;

    std::cout << "Account number: ";
    std::getline(std::cin, accNum);
    if (accNum.empty()) std::getline(std::cin, accNum); // handle leftover newline

    std::cout << "Account holder name: ";
    std::getline(std::cin, holder);

    std::cout << "Initial balance (>= 0): ";
    while (!(std::cin >> initial) || initial < 0.0) {
        std::cout << "Enter a nonnegative number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return BankAccount(accNum, holder, initial);
}

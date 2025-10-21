#include "BankAccount.h"
#include <cstring>
#include <limits>
#include <ctime>

static std::string makeTimestamp() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&tm, &t);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

char* BankAccount::allocCopy(const std::string& s) {
    char* p = new char[s.size() + 1];
    std::memcpy(p, s.c_str(), s.size() + 1);
    return p;
}

BankAccount::BankAccount()
    : accountNumber(nullptr), accountHolderName(nullptr), balance(0.0) {}

BankAccount::BankAccount(std::string accNum, std::string holder, double bal)
    : accountNumber(allocCopy(accNum)),
      accountHolderName(allocCopy(holder)),
      balance(bal >= 0.0 ? bal : 0.0) {}

BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(nullptr), accountHolderName(nullptr), balance(0.0) {
    if (other.accountNumber)      accountNumber = allocCopy(other.accountNumber);
    if (other.accountHolderName)  accountHolderName = allocCopy(other.accountHolderName);
    balance = other.balance;
    transactionHistory = other.transactionHistory;
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        char* newNum  = other.accountNumber     ? allocCopy(other.accountNumber)     : nullptr;
        char* newName = other.accountHolderName ? allocCopy(other.accountHolderName) : nullptr;
        delete[] accountNumber;
        delete[] accountHolderName;
        accountNumber = newNum;
        accountHolderName = newName;
        balance = other.balance;
        transactionHistory = other.transactionHistory;
    }
    return *this;
}

BankAccount::~BankAccount() {
    delete[] accountNumber;
    delete[] accountHolderName;
}

void BankAccount::logTransaction(const std::string& type, double amount) {
    Transaction t;
    t.type = type;
    t.amount = amount;
    t.timestamp = makeTimestamp();
    transactionHistory.push_back(t);
}

void BankAccount::printHistory() const {
    if (transactionHistory.empty()) {
        std::cout << "No transactions recorded.\n";
        return;
    }
    std::cout << "Transaction history for "
              << (accountHolderName ? accountHolderName : "(unknown)") << ":\n";
    for (const auto& t : transactionHistory) {
        std::cout << " - " << t.timestamp << " | " << t.type
                  << " | $" << t.amount << '\n';
    }
}

bool BankAccount::Deposit(double amount) {
    if (amount <= 0.0) return false;
    balance += amount;
    logTransaction("Deposit", amount);
    return true;
}

bool BankAccount::Withdraw(double amount) {
    if (amount <= 0.0) return false;
    if (amount > balance) return false;
    balance -= amount;
    logTransaction("Withdrawal", amount);
    return true;
}

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

std::string BankAccount::GetAccountNumber() const {
    return accountNumber ? std::string(accountNumber) : std::string();
}

std::string BankAccount::GetAccountHolderName() const {
    return accountHolderName ? std::string(accountHolderName) : std::string();
}

double BankAccount::GetBalance() const {
    return balance;
}

void BankAccount::SetAccountHolderName(const std::string& newName) {
    char* tmp = allocCopy(newName);
    delete[] accountHolderName;
    accountHolderName = tmp;
}

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
    if (accNum.empty()) std::getline(std::cin, accNum);

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

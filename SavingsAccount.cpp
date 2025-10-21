#include "SavingsAccount.h"
#include <iostream>
using namespace std;

// constructor calls base class constructor and sets interest rate
SavingsAccount::SavingsAccount(string accNum, string holder, double bal, double rate)
    : BankAccount(accNum, holder, bal) {
    interestRate = rate;
}

// adds interest to the account balance
void SavingsAccount::CalculateInterest() {
    double interest = GetBalance() * interestRate;
    Deposit(interest);
    cout << "Interest of $" << interest << " added to balance." << endl;
}

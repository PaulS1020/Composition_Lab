#include "CheckingAccount.h"
#include <iostream>
using namespace std;

CheckingAccount::CheckingAccount(string accNum, string holder, double bal, double fee)
    : BankAccount(accNum, holder, bal) {
    transactionFee = fee;
}

bool CheckingAccount::Withdraw(double amount) {
    double total = amount + transactionFee;
    if (total <= GetBalance()) {
        BankAccount::Withdraw(total);
        cout << "Withdrew $" << amount << " plus a fee of $" << transactionFee << endl;
        return true;
    }
    else {
        cout << "Not enough funds for withdraw + fee." << endl;
        return false;
    }
}

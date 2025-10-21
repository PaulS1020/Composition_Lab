/*
Name: Paul Soy
 Date: October 13, 2025
 Assignment: Lab Activities: Inheritance
 Purpose: Inheritance and polymorphism using BankAccount classes
*/

#include <iostream>
#include <vector>
#include "CheckingAccount.h"
#include "SavingsAccount.h"
using namespace std;

int main() {
 vector<BankAccount*> accounts; // vector of base class pointers

 // create derived class objects
 CheckingAccount* checking = new CheckingAccount("CHK1001", "Paul", 1000.0, 2.5);
 SavingsAccount* savings = new SavingsAccount("SAV2001", "Paul Soy", 2000.0, 0.05);

 // store them in the vector
 accounts.push_back(checking);
 accounts.push_back(savings);

 cout << "\n     Starting Balances    " << endl;
 for (auto acc : accounts) {
  BankAccount::printAccount(*acc);
 }

 cout << "\n     Withdrawals    " << endl;
 // demonstrate polymorphism: Withdraw called through base class pointer
 accounts[0]->Withdraw(100); // calls CheckingAccount's version (adds fee)
 accounts[1]->Withdraw(100); // calls BankAccount's version (normal)

 cout << "\nBalances After Withdrawals    \n " << endl;
 for (auto acc : accounts) {
  BankAccount::printAccount(*acc);
 }

 cout << "\n Adding Interest to Savings    \n " << endl;
 // downcast to call the derived function
 SavingsAccount* sPtr = dynamic_cast<SavingsAccount*>(accounts[1]);
 if (sPtr != nullptr) {
  sPtr->CalculateInterest();
 }

 cout << "\n    Final Balances    " << endl;
 for (auto acc : accounts) {
  BankAccount::printAccount(*acc);
 }

 // clean up memory
 for (auto acc : accounts) {
  delete acc;
 }

 return 0;
}
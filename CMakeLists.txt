cmake_minimum_required(VERSION 4.0)
project(Inheritance)

set(CMAKE_CXX_STANDARD 20)

add_executable(Inheritance main.cpp
        BankAccount.cpp
        BankAccount.h
        CheckingAccount.h
        CheckingAccount.cpp
        SavingsAccount.h
        SavingsAccount.cpp
        Transaction.h)

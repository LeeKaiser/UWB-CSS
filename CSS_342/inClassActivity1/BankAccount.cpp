#include "BankAccount.h"

BankAccount::BankAccount()
{
    this->name = "name";
    this->year = 0;

}
BankAccount::BankAccount(string name, int year)
{
    this->name = name;
    this->year = year;

}
BankAccount::~BankAccount()
{
    cout << "used destructor"
}
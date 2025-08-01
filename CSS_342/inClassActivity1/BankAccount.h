#include <iostream>
using namespace std;

class BankAccount()
{
    public:
    //constructor
    BankAccount();
    BankAccount(string name, int year);
    ~BankAccount();

    private:
    string name;
    int year;
};
#include "Child.h"

Child::Child()
{

}

Child::Child(string fName, string lName, int Age)
{
    age = Age;
    firstName = fName;
    lastName = lName;
}

Child::Child(Child const &obj)
{
    age = obj.getAge();
    firstName = obj.getFirst();
    lastName = obj.getLast();
}

Child::~Child()
{

}

int Child::getAge() const
{
    return age;
}

string Child::getName() const
{
    return firstName + lastName;
}

bool Child::operator<(const Child &obj) const
{
    if (age < obj.getAge())
    {
        return true;
    }
    return false;
}
bool Child::operator<=(const Child &obj) const
{
    if (*this == obj || *this < obj)
    {
        return true;
    }
    return false;
}
bool Child::operator>(const Child& obj) const
{
    if (*this >= obj)
    {
        return false;
    }
    return true;
}
bool Child::operator>=(const Child& obj) const
{
    if (*this > obj)
    {
        return false;
    }
    return true;
}
bool Child::operator==(const Child &obj) const
{
    if (age == obj.getAge() && firstName == obj.getFirst() && lastName == obj.getLast())
    {
        return true;
    } else{
        return false;
    }
}
bool Child::operator!=(const Child& obj) const
{
    if (*this == obj )
    {
        return false;
    }
    return true;
}

ostream &operator<<(ostream &os, const Child &obj)
{
    return os << obj.getName() << obj.getAge() << endl;
}

istream &operator>>(istream &is, Child &obj)
{
    int Age;
    string FirstN;
    string LastN;
    cout << "First Name:";
    is >> FirstN;
    cout << "Last Name:";
    is >> LastN;
    cout << "Age:";
    is >> Age;
    Child x(FirstN,LastN,Age);
    obj = x;
    return is;

}
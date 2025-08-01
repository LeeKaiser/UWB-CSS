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
    lastName =obj.getLast();
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

string Child::getFirst() const
{
    return firstName;
}
string Child::getLast() const
{
    return lastName;
}

bool Child::operator<(const Child &obj) const
{
    if (getLast() < obj.getLast())
    {
        //compare last name first
        return true;
    } else if (getLast() == obj.getLast() && getFirst() < obj.getFirst())
    {
        //if last name is same, compare first name
        return true;
    }
    else if ((getLast() == obj.getLast() && getFirst() == obj.getFirst()) && getAge() < obj.getAge())
    {
        //if name is same, compare age
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
bool Child::operator>(const Child &obj) const
{
    if (*this <= obj)
    {
        return false;
    }
    return true;
}
bool Child::operator>=(const Child &obj) const
{
    if (*this > obj)
    {
        return false;
    }
    return true;
}
bool Child::operator==(const Child &obj) const
{
    if (age == obj.getAge() && getName() == obj.getName())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Child::operator!=(const Child &obj) const
{
    if (*this == obj)
    {
        return false;
    }
    return true;
}

ostream &operator<<(ostream &os, const Child &obj)
{
    return os << obj.getName() << obj.getAge();
}

istream &operator>>(istream &is, Child &obj)
{
    string fName;
    string lName;
    int ageVal;
    is >> fName >> lName >> ageVal;
    Child x(fName , lName, ageVal);
    obj = x;
    return is;
}
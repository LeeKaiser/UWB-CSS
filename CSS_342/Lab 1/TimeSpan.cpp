#include "TimeSpan.h"

TimeSpan::TimeSpan()
{
    /*
    TimeSpan constructor method
    perimeter: none

    It constructs a TimeSpan object with 0,0,0 time
    */
    setTime(0, 0, 0);
}

TimeSpan::TimeSpan(double hours, double minutes, double seconds)
{
    /*
    TimeSpan constructor method
    perimeter: hours (integer), minutes (integer), seconds (integer)

    It constructs a TimeSpan object and determines the value of
    Hour, Minutes, and Second variables.
    */
    // run correct numbers for minutes & seconds as well as hours & minutes
    // to make sure the numbers are converted correctly and safe to be converted to int from double
    correctNumbers(minutes, seconds);
    correctNumbers(hours, minutes);
    correctNumbers(minutes, seconds);
    // set time method
    setTime((int)hours, (int)minutes, (int)seconds);
}

TimeSpan::~TimeSpan()
{
    // cout << "destructor called" << endl;
}

int TimeSpan::getHours() const
{
    /*
    getHours Accessor method
    perimeter: n/a

    It returns the value of Hour
    */
    return hour;
}

int TimeSpan::getMinutes() const
{
    /*
    getMinutes Accessor method
    perimeter: n/a

    It returns the value of Minute
    */
    return minute;
}

int TimeSpan::getSeconds() const
{
    /*
    getSeconds Accessor method
    perimeter: n/a

    It returns the value of Second
    */
    return second;
}

bool TimeSpan::setTime(const int &hours, const int &minutes, const int &seconds)
{
    /*
    setTime Mutator method
    perimeter: hours (integer), minutes (integer), seconds (integer)

    It sets the value of Hour,Minute,Second
    */

    this->hour = hours;
    this->minute = minutes;
    this->second = seconds;
    return true;
}

void TimeSpan::correctNumbers(double &higherVal, double &lowerVal) const
{
    /*
    correctNumbers method
    perimeter: higherUnit, lowerUnit

    makes it so that the time units are scaled properately and rounded.
    if the higher value and lower value has different positivity, make appropriate adjustment
    */

    // move lower val higher than 60 to higher val
    if (lowerVal > 60 || lowerVal < -60)
    {
        // turn time unit exceeding 60 to higher unit
        int highFromLow = lowerVal / 60;
        higherVal += (double)highFromLow;
        // remove the time converted to higher unit from lowerVal
        lowerVal = lowerVal - highFromLow * 60;
    }

    // get the decimal of higherVal
    int highBaseNo = (int)higherVal;
    double highRemainder = higherVal - (double)highBaseNo;

    // remove the remainder from higher unit
    higherVal -= highRemainder;
    // add remainder of higher unit to lower unit
    lowerVal += highRemainder * 60;
    // round lower unit
    int lowBaseNo = (int)lowerVal;
    double lowRemainder = lowerVal - (double)lowBaseNo;
    lowerVal -= lowRemainder;
    if (lowerVal < 0 && lowRemainder < -0.5)
    {
        // base number is negative and remainder is less than -0.5
        lowerVal--;
    }
    else if (lowerVal >= 0 && lowRemainder >= 0.5)
    {
        // base number is positive and remainder is greater than 0.5
        lowerVal++;
    }

    // when higherval is is negative and lowerval is positive
    if (higherVal < 0 && lowerVal > 0)
    {
        higherVal++;
        lowerVal -= 60;
    }
    else if (higherVal > 0 && lowerVal < 0)
    {
        higherVal--;
        lowerVal += 60;
    }
}

TimeSpan TimeSpan::operator+(TimeSpan const &obj) const
{
    /*
    + operator overload
    perimeter: n/a


    overload + to make it add all values of time span onto a different values of time span


    */
    TimeSpan ret(hour + obj.getHours(), minute + obj.getMinutes(), second + obj.getSeconds());
    return ret;
}

TimeSpan TimeSpan::operator-(TimeSpan const &obj) const
{
    /*
    - unary negation overload
    perimeter: n/a


    subtract value of one time span on different time span


    */
    TimeSpan ret(hour - obj.getHours(), minute - obj.getMinutes(), second - obj.getSeconds());
    return ret;
}

TimeSpan TimeSpan::operator-() const
{
    /*
    - unary negation overload
    perimeter: n/a


    invert positivity of all values
    */
    TimeSpan ret; // create 0,0,0
    ret -= *this;
    return ret;
}

bool TimeSpan::operator==(TimeSpan const &obj) const
{
    /*
    == operator overload
    perimeter: n/a


    retrun true if all values are same
    */
    if (hour == obj.getHours() && minute == obj.getMinutes() && second == obj.getSeconds())
    {
        return true;
    }
    return false;
}

bool TimeSpan::operator!=(TimeSpan const &obj) const
{
    /*
    != operator overload
    perimeter: n/a


    return false if all values are same
    */
    if (*this == obj)
    {
        return false;
    }
    return true;
}

TimeSpan &TimeSpan::operator+=(TimeSpan const &obj)
{
    /*
    += operator overload
    perimeter: n/a


    add obj to a timespan object
    */
    *this = *this + obj;
    return *this;
}

TimeSpan &TimeSpan::operator-=(TimeSpan const &obj)
{
    /*
    -= operator overload
    perimeter: n/a


    subtract obj to a timespan object
    */
    *this = *this - obj;
    return *this;
}

ostream &operator<<(ostream &os, const TimeSpan &cr)
{
    /*
    << operator overload
    perimeter: n/a

    return string value in Hours: hours, Minutes: minutes, Seconds: seconds
    format
    */
    return os << "Hours: " << cr.getHours() << ", Minutes:" << cr.getMinutes() << ", Seconds:" << cr.getSeconds();
}

istream &operator>>(istream &is, TimeSpan &cr)
{
    /*
    >> operator overload
    perimeter: n/a

    show three prompts that determine the Hour, Minute, and Second.
    */
    double h; // represent hours input
    double m; // represent minutes input
    double s; // represent seconds input
    cout << "Hours:";
    is >> h;
    cout << "Mins:";
    is >> m;
    cout << "Secs:";
    is >> s;
    TimeSpan x(h, m, s);
    cr = x;
    return is;
    // cr.setTime(h, m, s);
}

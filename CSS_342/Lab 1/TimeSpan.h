#include <iostream>
using namespace std;

class TimeSpan
{
public:
    // constructors
    TimeSpan();
    TimeSpan(double hours, double minutes, double seconds);
    ~TimeSpan();

    // accessors
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    // mutator
    bool setTime(const int &hours, const int &minutes, const int &seconds);

    // overload operators
    TimeSpan operator+(TimeSpan const &obj) const;
    TimeSpan operator-(TimeSpan const &obj) const;
    TimeSpan operator-() const;
    bool operator==(TimeSpan const &obj) const;
    bool operator!=(TimeSpan const &obj) const;
    TimeSpan &operator+=(TimeSpan const &obj);
    TimeSpan &operator-=(TimeSpan const &obj);
    friend ostream &operator<<(ostream &os, const TimeSpan &cr);
    friend istream &operator>>(istream &is, TimeSpan &cr);

private:
    // variables
    int hour;
    int minute;
    int second;

    // internal number correcting method
    void correctNumbers(double &higherVal, double &lowerVal) const;
};
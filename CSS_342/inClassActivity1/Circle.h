#include <iostream>
using namespace std;

class Circle
{
public:
    // constructor
    Circle();
    Circle(double x, double y, double r);
    ~Circle();

    // accessor and mutators
    double getRadius() const;
    double getX() const;
    double getY() const;

    void setRadius(double r);
    void setX(double x);
    void setY(double y);

    // other methods
    double calcArea() const;
    double calcPerimeter() const;
    bool isPointWithinCircle(const double x, const double y) const;

    Circle operator+(Circle const &obj);
    bool operator==(Circle const &obj) const;
    bool operator!=(Circle const &obj) const;
    Circle &operator+=(Circle const &obj);
    friend ostream &operator<<(ostream &os, const Circle &cr);

private:
    double xCord;
    double yCord;
    double rads;
};
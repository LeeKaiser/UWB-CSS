#include "Circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

Circle::Circle()
{
    xCord = 0;
    yCord = 0;
    rads = 1;
}

Circle::Circle(double x, double y, double r)
{
    if (r < 0)
    {
        throw runtime_error("used negative value for Radius");
    }
    this->xCord = x;
    this->yCord = y;
    this->rads = r;
}

Circle::~Circle()
{
    cout << "used destructor" << endl;
}

double Circle::getRadius() const
{
    return rads;
}

double Circle::getX() const
{
    return xCord;
}

double Circle::getY() const
{
    return yCord;
}

void Circle::setRadius(double r)
{
    rads = r;
}

void Circle::setX(double x)
{
    xCord = x;
}

void Circle::setY(double y)
{
    yCord = y;
}

double Circle::calcArea() const
{
    return M_PI * rads * rads;
}

double Circle::calcPerimeter() const
{
    return M_PI * rads * 2;
}

bool Circle::isPointWithinCircle(const double x, const double y) const
{
    // Pythagorean theorem
    double distX = xCord - x;
    double distY = yCord - y;
    double dist = sqrt((distX * distX) + (distY * distY));
    if (dist <= rads)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Circle Circle::operator+(Circle const &obj)
{
    Circle ret = Circle();
    ret.setRadius(rads + obj.getRadius());
    ret.setX(xCord + obj.getX());
    ret.setY(yCord + obj.getY());
    return ret;
}

bool Circle::operator==(Circle const &obj) const
{
    if (rads == obj.getRadius() && xCord == obj.getX() && yCord == obj.getY())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Circle::operator!=(Circle const &obj) const
{
    if (*this == obj)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Circle &Circle::operator+=(Circle const &obj)
{
    *this = *this + obj;
    return *this;
}

ostream &operator<<(ostream &os, const Circle &cr)
{
    return os << "(" << cr.xCord << ", " << cr.yCord << ", " << cr.rads << ")";
}
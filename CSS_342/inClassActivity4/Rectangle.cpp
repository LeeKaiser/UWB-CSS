#include <iostream>
using namespace std;

struct Rectangle
{
    int width;
    int length;
};

// int area(Rectangle rect)       call by value
// int area( Rectangle &rect)     call by reference 
int area(const Rectangle &rect)// call by const reference
{
    return rect.width * rect.length;
}

int main()
{
    Rectangle r = {3,3};

    cout << r.length << endl;
    cout << r.width << endl;
    cout << area(r) << endl;
}
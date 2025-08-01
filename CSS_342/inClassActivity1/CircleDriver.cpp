#include "Circle.h"

int main()
{
    try
    {
        Circle cir(0, 0, 1);
        cir.setRadius(5);
        cir.setX(3);
        cir.setY(9);

        cout << "radius:" << cir.getRadius() << endl;
        cout << "X:" << cir.getX() << endl;
        cout << "Y:" << cir.getY() << endl;
        cout << "Area:" << cir.calcArea() << endl;
        cout << "Perimeter:" << cir.calcPerimeter() << endl;
        cout << "is (1,2) within circle?:" << cir.isPointWithinCircle(1, 2) << endl;
        cout << "is (2,6) within circle?:" << cir.isPointWithinCircle(2, 6) << endl;

        try
        {
            Circle cir1(5, 2, 3);
            cout << "cir + cir1" << cir + cir1 << endl;
            cout << "cir = cir1:" << (cir == cir1) << endl;
            cout << "cir != cir1:" << (cir != cir1) << endl;
            cir += cir1;
            cout << "cir += cir1" << cir << endl;
            cout << "creating circle with negative radius" << endl;
            try
            {
                Circle cir2(2, 3, -5);
            }
            catch (const std::exception &e)
            {
                cout << "Runtime Error: " << e.what() << endl;
            }
        }
        catch (const std::exception &e)
        {
            cout << "Runtime Error: " << e.what() << endl;
        }
    }
    catch (runtime_error e)
    {
        cout << "Runtime Error: " << e.what() << endl;
    }
}
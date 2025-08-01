#include <iostream>
using namespace std;

struct Student
{
    int age;
    string name;
};

int main()
{
    Student s;
    s.age = 20;
    s.name = "Joe";

    cout << s.age << endl;
    cout << s.name << endl;

    // allocate memory on heap for student

    Student* p = new Student;
    
    p->age = 21;
    p->name = "Dave";

    cout << p->age << endl;

    delete p;
    return 0;
}
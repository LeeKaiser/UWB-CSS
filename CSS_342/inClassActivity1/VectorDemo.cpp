#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1 = {100, 200, 300};

    cout << "v1[0] = " << v1[0] << endl;
    cout << "&v1 = " << &v1 << endl;
    cout << "&v1[0] = " << &v1[0] << endl;
    cout << "&v1[1] = " << &v1[1] << endl;
    cout << "&v1[2] = " << &v1[2] << endl;

    v1.push_back(400);
    cout << "after push back" << endl;
    cout << "&v1[0] = " << &v1[0] << endl;
    cout << "&v1[1] = " << &v1[1] << endl;
    cout << "&v1[2] = " << &v1[2] << endl;
    cout << "&v1[3] = " << &v1[3] << endl;
    return 0;
}
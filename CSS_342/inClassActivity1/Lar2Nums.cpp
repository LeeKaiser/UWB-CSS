#include <iostream>
using namespace std;

template <class ItemType>
ItemType Lar2Nums(ItemType &a, ItemType &b)
{
    ItemType c = a;
    if (b > a)
    {
        c = b;
    }
    return c;
}

int main()
{
    string a = "a";
    string b = "b";
    cout << Lar2Nums(a, b) << endl;
    return 0;
}
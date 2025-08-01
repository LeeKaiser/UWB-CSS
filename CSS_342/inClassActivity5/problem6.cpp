#include <iostream>
#include <stack>
using namespace std;

int Sunset(int residents[],int size)
{
    stack<int> myStack;
    for (int i = 0; i < size; i++)
    {
        myStack.push(*(residents+i));
    }

    int ret = 0;
    int highest = 0;
    while(!myStack.empty())
    {
        if (myStack.top() > highest)
        {
            ret += 1;
            highest = myStack.top();
        }
        myStack.pop();
    }

    return ret;
}
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void Mirror(queue<int> &q)
{
    queue<int> copy;
    stack<int> myStack;

    while(!q.empty())
    {
        int x = q.front();
        copy.push(x);
        myStack.push(x);
        q.pop();
    }
    while (!myStack.empty())
    {
        copy.push(myStack.top());
        myStack.pop();
    }
    while(!copy.empty())
    {
        q.push(copy.front());
        copy.pop();
    }
}
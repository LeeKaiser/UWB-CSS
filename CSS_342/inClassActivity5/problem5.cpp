#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void Reverse(queue<int> &q)
{
    stack<int> myStack;
    while(!q.empty())
    {
        myStack.push(q.front());
        q.pop();
    }
    while(!myStack.empty())
    {
        q.push(myStack.top());
        myStack.pop();
    }
}
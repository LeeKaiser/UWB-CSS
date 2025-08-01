#include "problem5.cpp"
#include <queue>

int main()
{
    queue<int> myQueue;
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    Reverse(myQueue);
    while (!myQueue.empty())
    {
        cout << myQueue.front() << endl;
        myQueue.pop();
    }
}
#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(stack<int> s)
{
    stack<int> scopy, s2;
    scopy = s;
    int val;
    while(!s.empty())
    {
        val = s.top();
        s.pop();
        s2.push(val);
    }
    return scopy == s2;
}

int main()
{
    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(2);
    s.push(1);
    cout << "isPalindrome() : " << isPalindrome(s) << endl;

}
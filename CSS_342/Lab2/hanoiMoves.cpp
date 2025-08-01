#include <iostream>
#include <sys/time.h>
#include <cmath>
using namespace std;

bool printActive = true;

long counter;
struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (int)((endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec);
}

void hanoiMoves(int n, string from, string to, string extra);
void testHanoiMoves();

int main()
{
    // test n = 3
    cout << "n = 3" << endl;;
    int start = gettimeofday(&startTime, 0);
    hanoiMoves(3, "A", "C", "B");
    int end = gettimeofday(&endTime, 0);

    cout << "counter = " << counter << endl;
    cout << "time = " << elapsed(startTime, endTime) << " microseconds" << endl << endl;

    testHanoiMoves();
    return 0;
}

void testHanoiMoves()
{
    /*
    testHanoiMoves

    no param

    tests HanoiMoves from values of 1 to 15.
    print out amount of steps it takes to solve the puzzle.
    print out time it took to calculate the amount of steps it would take.

    */
    printActive = false;
    for (int i = 1; i <= 15; i++)
    {

        cout << "n = " << i << endl;
        int start = gettimeofday(&startTime, 0);
        hanoiMoves(i, "A", "C", "B");
        int end = gettimeofday(&endTime, 0);

        cout << "counter = " << counter << endl;
        cout << "2^n - 1 = " << pow(2, i) - 1 << endl;
        cout << "time = " << elapsed(startTime, endTime) << " microseconds" << endl << endl;
        counter = 0;
    }
    printActive = true;
}

void hanoiMoves(int n, string from, string to, string extra)
{
    if (n <= 0)
    {
    }
    else
    {
        // move all but bottom disk to the extra
        hanoiMoves(n - 1, from, extra, to);
        // print out the line that says the last disk moved to the "to" pole
        counter++;
        if (printActive)
        {
            cout << "Move disk " << n << " from " << from << " to " << to << endl;
        }

        // repeat same for n-1
        hanoiMoves(n - 1, extra, to, from);
    }
}
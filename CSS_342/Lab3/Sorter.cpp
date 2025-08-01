#include "SortImpls.cpp"
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (int)(((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
}
bool printEnabled = true;
string VectType = "Random";
int trialCount = 1;

vector<int> generateVectRandom(int length);
vector<int> generateVectOrdered(int length);
vector<int> generateVectPartial(int length);
vector<int> generateVectReverse(int length);
void printVector(vector<int> v);

void findSortType(string arg)
{
    // random by default
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: Sorter SORT_TYPE ARRAY_SIZE [YES|NO]" << endl;
        return -1;
    }
    string sortType = argv[1];
    int listLength = stoi(argv[2]);
    if (listLength < 1)
    {
        cerr << "ListLength below 1" << endl;
        return -1;
    }

    // determine if print should be enabled, and determine the type of starting list. only works as 3rd argument
    if (argc >= 4)
    {
        string printType = argv[3];
        if (printType == "NO")
        {
            printEnabled = false;
        }
    }
    // determine what the starting list type is, default is random. only works as 4th argument
    if (argc >= 5)
    {
        string printType = argv[4];
        if (printType == "Ordered" || printType == "Partial" || printType == "Reversed")
        {
            VectType = printType;
        }
    }
    // determine the amount of trials done. default is 1
    if (argc >= 6)
    {
        trialCount = stoi(argv[5]);
        if (trialCount < 1)
        {
            cerr << "trial count should be above 0" << endl;
            return -1;
        }
    }
    vector<int> vectOfTimeSpent(trialCount);
    for (auto i = vectOfTimeSpent.begin(); i < vectOfTimeSpent.end(); i++)
    {
        // generate vector
        vector<int> testVect;
        if (VectType == "Random")
        {
            testVect = generateVectRandom(listLength);
        }
        else if (VectType == "Ordered")
        {
            testVect = generateVectOrdered(listLength);
        }
        else if (VectType == "Reversed")
        {
            testVect = generateVectReverse(listLength);
        }
        else if (VectType == "Partial")
        {
            testVect = generateVectPartial(listLength);
        }
        else
        {
            cerr << "list type not understood" << endl;
        }

        // print out list before sorting
        if (printEnabled)
        {
            cout << "Initial:" << endl;
            printVector(testVect);
        }

        // do sort
        gettimeofday(&startTime, 0);

        if (sortType == "BubbleSort")
        {
            BubbleSort(testVect, listLength);
        }
        else if (sortType == "InsertionSort")
        {
            InsertionSort(testVect, listLength);
        }

        else if (sortType == "MergeSort")
        {
            MergeSort(testVect, 0, listLength - 1);
        }

        else if (sortType == "QuickSort")
        {
            QuickSort(testVect, 0, listLength - 1);
        }
        else if (sortType == "ShellSort")
        {
            ShellSort(testVect, listLength);
        }
        else
        {
            cerr << "sort type not understood" << endl;
        }

        gettimeofday(&endTime, 0);

        // print out list after sorting
        if (printEnabled)
        {
            cout << "Sorted:" << endl;
            printVector(testVect);
        }
        int elapsedTime = elapsed(startTime, endTime);
        cout << "time (ms): " << elapsedTime << endl;

        *i = elapsedTime;
    }
    // only print average time if trial count is greater than 1
    if (trialCount > 1)
    {
        int sumTimeSpent = 0;
        for (int i = 0; i < trialCount; i++)
        {
            sumTimeSpent += vectOfTimeSpent[i];
        }
        int avgTimeSpent = sumTimeSpent / 3;
        cout << "average time (ms): " << avgTimeSpent << endl;
    }
    cout << endl;
    return 0;
}

vector<int> generateVectRandom(int length)
{
    /*
        generateVectRandom(int length)
        generates random vector to be used for sorting

        length - length of the vector

        returns a vecotr<int>
    */
    vector<int> ret(length);

    for (auto i = ret.begin(); i < ret.end(); i++)
    {
        int x = rand() % length;
        *i = x;
    }

    return ret;
}

vector<int> generateVectOrdered(int length)
{
    /*
        generateVectOrdered(int length)
        generates Ordered vector to be used for sorting

        length - length of the vector

        returns a vecotr<int>
    */
    vector<int> ret(length);
    int index = 0;
    for (auto i = ret.begin(); i < ret.end(); i++)
    {
        index++;
        *i = index;
    }

    return ret;
}

vector<int> generateVectReverse(int length)
{
    /*
        generateVectReverse(int length)
        generates reversed vector to be used for sorting

        length - length of the vector

        returns a vecotr<int>
    */
    vector<int> ret(length);
    int index = length;
    for (auto i = ret.begin(); i < ret.end(); i++)
    {
        index--;
        *i = index;
    }

    return ret;
}

vector<int> generateVectPartial(int length)
{
    /*
        generateVectPartial(int length)
        generates Partially sorted vector to be used for sorting

        length - length of the vector

        returns a vecotr<int>
    */
    vector<int> ret(length);
    int index = 3;

    for (auto i = ret.begin(); i < ret.end(); i++)
    {
        // each value should have a variation of 3
        int x = rand() % 6 - 3;
        index++;
        *i = index + x;
    }

    return ret;
}

void printVector(vector<int> v)
{

    for (int i = 0; i < v.size(); i++)
    {
        cout << "items[" << i << "]" << v[i] << endl;
    }
}
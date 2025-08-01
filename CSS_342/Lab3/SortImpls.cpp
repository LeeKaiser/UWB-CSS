#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b)
{
    /*
        swap(int &a, int &b)
        swap the values between two elements

        a- element 1
        b- element 2
    */
    int c = a;
    a = b;
    b = c;
}

void BubbleSort(vector<int>& vec, int length, int index1 = -1, int index2 = -1)
{
    /*
    BubbleSort(vector<int>& vec, int length, int index1 = -1, int index2 = -1)
    sort Vector vec of length n using bubble sort.

    vec - vector that needs to be sorted
    lenght - length of the vector
    index1 - optional minimum value
    index2 - optional maximum value
    */

    //modification: terminate the method if no swaps has been made in second loop, which implies the list has finished sorting

    bool swapped = false;
    //if no input is made for index1 and 2, then set those to these default values
    if (index1 == -1)
    {
        index1 = 0;
    }
    if (index2 == -1)
    {
        index2 = length;
    }
    //sorting
    for (int i = index2 - 1; i > 0; i--)
    {
        swapped = false;
        for (int j = index1; j < i; j++)
        {
            if (vec[j] > vec[j + 1])
            {
                
                // swap between two values if elemet j is greater than element above it
                swapped = true;
                swap(vec[j], vec[j + 1]);
            }
        }
        if (!swapped)
        {
            i = 0;
        }
    }
}

void InsertionSort(vector<int>& vec, int length)
{
    /*
        InsertionSort(vector<int>& vec, int length)
        sort Vector vec of length n using insertion sort.

        vec - vector that needs to be sorted
        lenght - length of the vector
    */

    for (int i = 1;i<length;i++)
    {
        int v = vec[i];
        int j = i-1;
        while (j>= 0 && vec[j] > v)
        {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = v;
    }
}

void merge(vector<int> &vec, int first, int mid, int last)
{
    /*
        merge(vector<int>& vec,int first,int mid,int last)
        sort Vector vec of length n using Merge sort.

        vec - vector that needs to be sorted
        first - first in the index
        last - last index
    */

    // temporary vector
    vector<int> tempVec(vec.size());

    // local indicies
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;

    int index = first1;
    while ((first1 <= last1) && (first2 <= last2))
    {
        // if first is smaller, put it in the temp vector
        if (vec[first1] <= vec[first2])
        {
            
            tempVec[index] = vec[first1];
            first1++;
        }
        // if second is smaller, put it in the temp vector
        else
        {
            
            tempVec[index] = vec[first2];
            first2++;
        }
        index++;
    }
    // finish adding first half if not done
    while (first1 <= last1)
    {
        
        tempVec[index] = vec[first1];
        first1++;
        index++;
    }
    // finish adding second half if not done
    while (first2 <= last2)
    {
        
        tempVec[index] = vec[first2];
        first2++;
        index++;
    }

    // copy the temp vector into base vector
    for (int i = first; i <= last; i++)
    {
        
        vec[i] = tempVec[i];
    }
}

void MergeSort(vector<int>& vec, int first, int last)
{
    /*
        MergeSort(vector<int>& vec, int first, int last)
        sort Vector vec of length n using Merge sort.

        vec - vector that needs to be sorted
        first - first in the index
        last - last index
    */
    if (first < last)
    {
        int mid = first + (last - first) / 2 ;//mid point
        //recurion
        MergeSort(vec,first,mid);
        MergeSort(vec, mid + 1, last);
        //merge
        merge(vec,first,mid,last);
    }
}

int partition(vector<int> &vec, int first, int last)
{
    // choose pivot then reposition it
    int mid = first + (last - first) /2;
    //sort firstmiddlelast
    if (vec[first] > vec[mid])
    {
        swap(vec[first],vec[mid]);
    }
    if (vec[mid] > vec[last])
    {
        swap(vec[mid], vec[last]);
    }
    if (vec[first] > vec[mid])
    {
        swap(vec[first], vec[mid]);
    }
    //mid is pivot index and placed before last
    swap(vec[mid], vec[last-1]);
    int pivotIndex = last - 1;
    int pivot = vec[pivotIndex];

    //deter,mine regions s1 and s2
    int indexFromLeft = first + 1;
    int indexFromRight = last - 2;

    bool done = false;
    while (!done)
    {
        while (vec[indexFromLeft] < pivot)
        {
            indexFromLeft++;
        }

        while (vec[indexFromRight] > pivot)
        {
            indexFromRight--;
        }
        if (indexFromLeft < indexFromRight)
        {
            swap(vec[indexFromLeft] , vec[indexFromRight]);
            indexFromLeft++;
            indexFromRight--;
        }
        else
        {
            done = true;
        }
    }

    swap(vec[pivotIndex],vec[indexFromLeft]);
    pivotIndex = indexFromLeft;

    return pivotIndex;
}

void QuickSort(vector<int> &vec, int first, int last)
{
    /*
        QuickSort(vector<int>& vec, int first, int last)
        sort Vector vec of length n using quick sort.

        vec - vector that needs to be sorted
        first - first in the index
        last - last index
    */

    if ((last - first + 1) < 4)
    {
        BubbleSort(vec, vec.size(), first ,last);
    }
    else 
    {
        int pivotIndex = partition(vec,first,last);

        QuickSort(vec,first,pivotIndex-1);
        QuickSort(vec,pivotIndex+1,last);
    }

}

void ShellSort(vector<int> &vec, int length)
{
    int gaps[] = {701,301,132,57,23,10,4,1};

    for (int gap : gaps)
    {
        
        for (int i = gap; i < length; i++)
        {
            int temp = vec[i];
            int j;
            for (j = i; (j >= gap) && (vec[j - gap] > temp); j-=gap)
            {
                vec[j] = vec[j-gap];
            }
            vec[j] = temp;
        }
    }
}
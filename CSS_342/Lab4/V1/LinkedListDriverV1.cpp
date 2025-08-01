#include "LinkedListV1.h"
#include "Child.h"

int main()
{
    
    

    LinkedList<int> intList;
    //generating list through insert 
    cout << "created new list<int>" << endl;
    cout << intList << endl;
    //edge case first element
    int a = 6;
    cout << "inserting " << a << " in the list: " ;
    cout << intList.Insert(&a) << endl;
//edge case inserting on front
    a = 3;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    cout << intList << endl;
    a = 2;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    cout << intList << endl;
    // failure case duplicate
    a = 3;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    a = 2;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    //edge case insert last
    a = 15;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    // average case
    a = 5;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;
    a = 1;
    cout << "inserting " << a << " in the list: ";
    cout << intList.Insert(&a) << endl;

    cout << intList << endl;
    //average case peek
    a = 3;
    int result;
    cout << "peeking " << a << ": ";
    cout << intList.Peek(a,result) << endl;
    cout << "result: " << result << endl;
// edge case first item peek
    a = 1;
    cout << "peeking " << a << ": ";
    cout << intList.Peek(a, result) << endl;
    cout << "result: " << result << endl;
// edge case last item peek
    a = 15;
    cout << "peeking " << a << ": ";
    cout << intList.Peek(a, result) << endl;
    cout << "result: " << result << endl;
//failure case no item found
    a = 10;
    cout << "peeking " << a << ": ";
    cout << intList.Peek(a, result) << endl;
    cout << "result: " << result << endl;
//removing average case
    a = 2;
    cout << "removing " << a << ": ";
    cout << intList.Remove(a, result) << endl;
    cout << "result: " << result << endl;
//list check
    cout << intList << endl;
//removing edge case first item
    a = 1;
    cout << "removing " << a << ": ";
    cout << intList.Remove(a, result) << endl;
    cout << "result: " << result << endl;
    //list check
    cout << intList << endl;
//removing edge case last item
    a = 15;
    cout << "removing " << a << ": ";
    cout << intList.Remove(a, result) << endl;
    cout << "result: " << result << endl;
    //list check
    cout << intList << endl;

//removing faulure case item not found
    a = 10;
    cout << "removing " << a << ": ";
    cout << intList.Remove(a, result) << endl;
    cout << "result: " << result << endl;
    // list check
    cout << intList << endl;

    //deleteList test average case
    cout << "deleting list" << endl;
    intList.DeleteList();
    cout << "printing deleted list:" << endl;
    cout << intList << endl;
    cout << "check if list is empty:" << endl;
    cout << "result: " << intList.isEmpty() << endl;
    //

    return 0;
}
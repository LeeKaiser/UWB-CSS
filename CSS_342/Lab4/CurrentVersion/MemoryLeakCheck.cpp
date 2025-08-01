#include "LinkedList.h"
#include "Child.h"

int main()
{
    cout << "testing buildList" << endl;
    LinkedList<Child> childList2;
    cout << childList2.BuildList("./MemoryLeakFile.txt") << endl;
    cout << childList2 << endl;
    LinkedList<Child> childList1;
    cout << childList1.BuildList("./MemoryLeakFile1.txt") << endl;
    cout << childList1 << endl;
    cout << childList1 + childList2 << endl;
    cout << childList1 << endl;
    childList1 += childList2;
    cout << childList1 << endl;
}
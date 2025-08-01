#include "LinkedList.h"
#include "Child.h"

int main()
{
    
    Child c1("Abby", "leg", 5); 
    Child c2("Ben", "two", 9); 
    Child c3("finn", "finn", 3);

    //testing child copy constructor
    Child c4(c2);

    LinkedList<Child> childList;
    cout << "created new list<Child>" << endl;
    cout << childList << endl;
    cout << "Inserting Child objects" << endl;
    childList.Insert(&c1);
    childList.Insert(&c2);
    childList.Insert(&c3);
    childList.Insert(&c4);
    cout << childList << endl;

    cout << "Testing Remove" << endl;
    cout << childList.Remove(c1, c1) << endl;
    cout << childList.Remove(c1,c1) << endl;

    cout << "Testing Peek" << endl;
    cout << childList.Peek(c2,c2) << endl;
    cout  << childList.Peek(c1,c1) << endl;

    cout << "testing delete list, and printing it" << endl;
    childList.DeleteList();
    cout << childList << endl;
    cout << "is empty: " << childList.isEmpty() << endl;

    //reassemble the list
    cout << "reassembling the list" << endl;
    childList.Insert(&c1);
    childList.Insert(&c2);
    childList.Insert(&c3);


    //generating another list to test merge    
    LinkedList<Child> childList1;
    Child c5("bob", "l", 5);
    Child c6("Ben", "twenty", 6);
    Child c7("finn", "finn", 3);
    childList1.Insert(&c5);
    childList1.Insert(&c6);
    childList1.Insert(&c7);
    cout << "created new child list to test merge" << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;
    cout << "merging childlist and childlist1" << endl;
    cout << childList.Merge(childList1) << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;
    //merging an empty list into a full list
    cout << "merging childlist1 (empty) into childlist" << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;
    cout << childList.Merge(childList1) << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;
    // merging a full list into an empty list
    cout << "merging childlist1 (empty) into childlist" << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;
    cout << childList1.Merge(childList) << endl;
    cout << "childlist: " << childList << endl;
    cout << "childlist1: " << childList1 << endl;

    cout << "result of merging the same list: " << childList1.Merge(childList1) << endl;
    
    cout << "testing buildList" << endl;
    LinkedList<Child> childList2;
    cout << childList2.BuildList("./TestFile.txt") << endl;
    cout << childList2 << endl;

    cout << "test copy constructor" << endl;
    LinkedList<Child> childList2Copy(childList2);
    cout << childList2Copy << endl;
    LinkedList<Child> childListCopyConstructFail(childList);
    cout << childListCopyConstructFail << endl;

    cout << "test + operator" << endl;
    cout << childList1 << endl;
    cout << childList2 << endl;
    cout << childList1 + childList2 << endl;
    cout << childList1 << endl;
    cout << childList2 << endl;

    cout << "test += and = operator" << endl;
    cout << childList1 << endl;
    childList1 += childList2;
    cout << childList1 << endl;
    cout << childList2 << endl;
    childList2 = childList1;
    cout << childList2 << endl;

    cout << "test == and != operator" << endl;
    cout << "childList1 == childList2: " << (childList1 == childList2) << endl;
    cout << "childList1 != childList2Copy: " << (childList1 != childList2Copy) << endl;

    //test with other types

    cout << "testing with string" << endl;
    LinkedList<string> stringList;
    LinkedList<string> stringList1;

    string s = "A";
    stringList.Insert(&s);
    s = "Man";
    stringList.Insert(&s);
    s = "Has";
    stringList.Insert(&s);
    s = "Fallen";
    stringList.Insert(&s);
    s = "Into";
    stringList.Insert(&s);
    s= "A";
    stringList.Insert(&s);
    s= "River";
    stringList.Insert(&s);
    s= "In";
    stringList.Insert(&s);
    s= "Lego";
    stringList.Insert(&s);
    s= "City";
    stringList.Insert(&s);

    cout << stringList << endl;

    s = "Start";
    stringList1.Insert(&s);
    s = "The";
    stringList1.Insert(&s);
    s = "Rescue";
    stringList1.Insert(&s);
    s = "Helecopter";
    stringList1.Insert(&s);

    cout << stringList1 << endl;

    cout << stringList + stringList1 << endl;
    stringList.Merge(stringList1);
    cout << stringList << endl;

    cout << stringList1 + stringList << endl;

    cout << "testing with ints" << endl;
    LinkedList<int> intList;
    LinkedList<int> intList1;

    int x = 27;
    intList.Insert(&x);
    x = 754;
    intList.Insert(&x);
    x = 27;
    intList.Insert(&x);
    x = 8;
    intList.Insert(&x);

    x = 27;
    intList1.Insert(&x);
    x = 754;
    intList1.Insert(&x);
    x = 27;
    intList1.Insert(&x);
    x = 8;
    intList1.Insert(&x);

    cout << intList + intList1 << endl;
    intList.Merge(intList1);
    cout << intList << endl;

    return 0;
}
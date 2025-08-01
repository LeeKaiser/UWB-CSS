#include "LinkedList.h"
#ifndef LinkedList_CPP
#define LinkedList_CPP

template <class ItemType>
LinkedList<ItemType>::LinkedList()
{
    /*
    default constructor

    head - Node object, which has null pItem and null next node.
    */
}

template <class ItemType>
LinkedList<ItemType>::LinkedList(LinkedList<ItemType> const &source)
{
    // Copy constructor

    *this = source;
}

template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    /*
    destructor

    activate DeleteList and also deletes head
    */
    DeleteList();
    delete head;
    head = nullptr;
}

template <class ItemType>
bool LinkedList<ItemType>::BuildList(string fileName)
{
    /*
    BuildList(string fileName)

    takes a file and uses it to add items into the list.
    */
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile.good())
    {
        return false;
    }
    while (!inFile.eof())
    {
        ItemType item;
        inFile >> item;
        Insert(&item);
    }
    inFile.close();
    return true;
}

template <class ItemType>
bool LinkedList<ItemType>::Insert(ItemType *obj)
{
    /*
    Insert(ItemType *obj)

    creates a copy of obj and puts it somewhere in the list. it does not allow duplicates.
    */

    ItemType *inputVar = new ItemType(*obj);
    // cout << *inputVar << endl;
    if (isEmpty())
    {
        // cout << "inserting first element" << endl;
        head->pItem = inputVar;
        return true;
    }

    // if smaller than head
    if (*head->pItem > *inputVar)
    {
        // cout << "obj smaller than head" << endl;
        Node *x = new Node(); // new head
        x->pItem = inputVar;
        Node *y = new Node(); // copy of current head
        y->pItem = head->pItem;
        y->next = head->next;
        delete head;
        x->next = y;
        head = x;
        return true;
    }
    // other cases
    Node *current = head;
    while (true)
    {

        // if current element is same as obj
        if (*inputVar == *current->pItem)
        {
            // cout << "current same as obj" << endl;
            delete inputVar;
            inputVar = nullptr;
            return false;
        }
        // if comparing with last element and is larger
        else if (current->next == NULL && *inputVar > *current->pItem)
        {
            // cout << "inserting at last" << endl;
            Node *x = new Node();
            x->pItem = inputVar;
            current->next = x;
            return true;
        }
        // if invutVar is larger than current element but smaller than next item
        else if (*current->next->pItem > *inputVar && *inputVar > *current->pItem)
        {
            // cout << "inserting between 2 elements" << endl;
            Node *x = new Node();
            x->pItem = inputVar;
            x->next = current->next;
            current->next = x;
            return true;
        }
        // if is larger but there is next element
        else if (*inputVar > *current->pItem)
        {
            // cout << "moving to next element" << endl;
            current = current->next;
        }
        else
        {
            // cout << "there must be a case that has not been factored" << endl;
            delete inputVar;
            inputVar = nullptr;
            return false;
        }
    }
    cout << "there has been a problem" << endl;
    return false;
}

template <class ItemType>
bool LinkedList<ItemType>::Remove(ItemType target, ItemType &result)
{
    /*
    Remove(ItemType target, ItemType &result)

    returns true and instantiates results if target exists in the list, also deleting the target. return false otherwise.
    */
    Node *current = head;

    if (current->pItem == NULL)
    {
        return false;
    }
    // when head is detected to be the item to be removed
    if (*head->pItem == target)
    {
        result = *head->pItem;
        if (head->next == NULL)
        {
            delete head->pItem;
            head->pItem = nullptr;
        }
        else
        {
            delete head->pItem;
            head->pItem = nullptr;
            head = head->next;
            delete current;
            current = nullptr;
        }

        return true;
    }

    Node *previous;

    while (true)
    {

        // when element other than first is detected to be removed
        if (*current->pItem == target)
        {
            result = *current->pItem;

            previous->next = current->next;
            delete current->pItem;
            current->pItem = nullptr;
            delete current;
            current = nullptr;
            return true;
        }
        // when reaching end of list and have not found anything
        else if (current->next == NULL)
        {
            return false;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

template <class ItemType>
bool LinkedList<ItemType>::Peek(ItemType target, ItemType &result) const
{
    /*
    Peek

    similar function as Remove but does not delete the target from the list
    */
    Node *current = head;

    while (true)
    {

        if (*current->pItem == target)
        {
            result = *current->pItem;
            return true;
        }
        else if (current->next == NULL)
        {
            return false;
        }
        else
        {
            current = current->next;
        }
    }
}

template <class ItemType>
void LinkedList<ItemType>::DeleteList()
{
    /*
    DeleteList()
    deletes all content in the list

    */
    while (head->pItem != NULL)
    {
        ItemType x;
        Remove(*head->pItem, x);
    }
}

template <class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    /*
    isEmpty()

    return true if there are no elements in the list
    */
    if (head->pItem == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class ItemType>
bool LinkedList<ItemType>::Merge(LinkedList &list1)
{
    /*
    Merge(LinkedList &list1)

    moves items from list1 into this list.
    */
    LinkedList<ItemType> *other = &list1;
    // make it check if the list passed in are the same
    if (this == other)
    {

        return false;
    }
    // section 1 - check if either lists are empty
    Node *current = head;
    ItemType x;

    // case in which the list1 is empty
    if (list1.head->pItem == NULL)
    {
        // cout << "No element to be merged" << endl;

        return true;
    }
    // case in which the list that list1 is merging into is empty
    if (current->pItem == NULL)
    {
        // cout << "the list was empty, and now will have same elements as list1" << endl;

        list1.Remove(*list1.head->pItem, x);
        this->Insert(&x);
        current = head;
    }

    // check if the first X is lower than head
    list1.Remove(*list1.head->pItem, x);
    if (*current->pItem > x)
    {

        this->Insert(&x);
        list1.Remove(*list1.head->pItem, x);
        current = head;
    }

    // other cases
    // *run through each element in base list and in cases where an element should be added, add it.
    // get the element to be added
    while (true)
    {
        // cout << "consider these elements: " << *current->pItem << ", " << x << endl;
        bool madeInsert = false;
        // when elements are same
        if (*current->pItem == x)
        {
            // cout << "equal elements, not added" << *current->pItem << ", " << x << endl;
            madeInsert = true;
        }

        // when inserting at the end
        else if (current->next == NULL)
        {
            // cout << "element added at end" << *current->pItem << ", " << x << endl;
            Node *newNode = new Node();
            ItemType *xPtr = new ItemType(x);
            newNode->pItem = xPtr;
            current->next = newNode;
            madeInsert = true;
        }

        // when iserting between elements
        else if (x > *current->pItem && *current->next->pItem > x)
        {
            // cout << "element added in middle" << *current->pItem << ", " << x << endl;
            Node *newNode = new Node();
            ItemType *xPtr = new ItemType(x);
            newNode->pItem = xPtr;
            newNode->next = current->next;
            current->next = newNode;
            madeInsert = true;
        }

        // progress current if no elements added
        if (!madeInsert)
        {
            // cout << "moving on in this list" << endl;
            current = current->next;
        }

        // check if there are more left in list1, if not, return true as the operation is complete.
        if (madeInsert && list1.head->pItem == NULL)
        {
            // cout << "finished" << endl;
            return true;
        }

        // progress list1 if element has been added
        if (madeInsert)
        {
            // cout << "moving on in list1" << endl;
            list1.Remove(*list1.head->pItem, x);
        }
    }

    // if there are still elements to add that are larger than highest value in the original list, then add the remaining items (if an error occures due to this reason)

    // cout << "something went wrong" << endl;
    return false;
}

template <class ItemType>
LinkedList<ItemType> LinkedList<ItemType>::operator+(LinkedList<ItemType> const &obj) const
{
    // create return list
    LinkedList<ItemType> ret;

    Node *currentThis = head;
    Node *currentObj = obj.head;
    Node *current = ret.head;

    // cout << "trigger 1" << endl;

    // check if either items are null
    if (currentThis->pItem == NULL && currentObj->pItem == NULL)
    {
        return ret;
    }

    // if only one of the lists are empty, return false
    else if (currentThis->pItem != NULL && currentObj->pItem == NULL)
    {
        ret = *this;
        return ret;
    }
    else if (currentThis->pItem == NULL && currentObj->pItem != NULL)
    {
        ret = obj;
        return ret;
    }

    // cout << "trigger 3" << endl;

    // add the first element first, the current element is empty and needs to have a special type of addition
    if (*currentThis->pItem < *currentObj->pItem)
    {
        ItemType x;
        Peek(*currentThis->pItem, x);
        ItemType *z = new ItemType(x);
        current->pItem = z;
        currentThis = currentThis->next;
    }
    else if (*currentThis->pItem > *currentObj->pItem)
    {
        ItemType x;
        obj.Peek(*currentObj->pItem, x);
        ItemType *z = new ItemType(x);
        current->pItem = z;
        currentObj = currentObj->next;
    }
    // if both are equal, just put in the element from this and skip ahead for both lists
    else
    {
        ItemType x;
        obj.Peek(*currentObj->pItem, x);
        ItemType *z = new ItemType(x);
        current->pItem = z;
        currentObj = currentObj->next;
        currentThis = currentThis->next;
    }

    // cout << "trigger 4" << endl;

    // both lists have objects, compare both of them
    bool objectRemaining = true;
    while (objectRemaining)
    {
        // cout << "trigger 5" << endl;
        bool fromThis = false;
        bool fromObj = false;
        // assemble list
        // if element in this is lesser than obj, put in the element from this
        if (*currentThis->pItem < *currentObj->pItem)
        {
            ItemType x;
            Peek(*currentThis->pItem, x);
            Node *y = new Node();
            ItemType *z = new ItemType(x);
            y->pItem = z;

            current->next = y;
            current = current->next;
            fromThis = true;
        }
        // if element in obj is lesser than this, put in the element from obj
        else if (*currentThis->pItem > *currentObj->pItem)
        {
            ItemType x;
            obj.Peek(*currentObj->pItem, x);
            Node *y = new Node();
            ItemType *z = new ItemType(x);
            y->pItem = z;

            current->next = y;
            current = current->next;
            fromObj = true;
        }
        // if both are equal, just put in the element from this and skip ahead for both lists
        else
        {
            ItemType x;
            Peek(*currentObj->pItem, x);
            Node *y = new Node();
            ItemType *z = new ItemType(x);
            y->pItem = z;

            current->next = y;
            current = current->next;
            fromThis = true;
            fromObj = true;
        }
        // cout << "trigger 6" << endl;
        if (currentThis->next == NULL && fromThis)
        {
            objectRemaining = false;
        }
        else if (currentObj->next == NULL && fromObj)
        {
            objectRemaining = false;
        }
        else
        {
            if (fromThis)
            {
                currentThis = currentThis->next;
            }
            if (fromObj)
            {
                currentObj = currentObj->next;
            }
        }
    }
    // cout << "trigger 7" << endl;
    //  reaches here when reacing end of one of the list
    //if both lists are null, return the list
    if (currentThis->next == NULL && currentObj->next == NULL)
    {
        return ret;
    }
    if (currentThis->next == NULL)
    {
        while (true)
        {
            ItemType x;
            obj.Peek(*currentObj->pItem, x);
            Node *y = new Node();
            ItemType *z = new ItemType(x);
            y->pItem = z;

            current->next = y;

            if (currentObj->next == NULL)
            {
                // cout << "trigger 8" << endl;
                return ret;
            }
            else
            {
                currentObj = currentObj->next;
                current = current->next;
            }
        }
    }
    else
    {
        while (true)
        {
            ItemType x;
            Peek(*currentThis->pItem, x);
            Node *y = new Node();
            ItemType *z = new ItemType(x);
            y->pItem = z;

            current->next = y;

            if (currentThis->next == NULL)
            {
                // cout << "trigger 9" << endl;
                return ret;
            }
            else
            {
                currentThis = currentThis->next;
                current = current->next;
            }
        }
    }

    return ret;
}

template <class ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::operator+=(LinkedList<ItemType> const &obj)
{
    *this = *this + obj;
    return *this;
}

template <class ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::operator=(LinkedList<ItemType> const &obj)
{
    DeleteList();

    Node *count = obj.head;
    if (count->pItem == NULL)
    {
        // source is empty and cannot proceed farther
    }
    else
    {

        ItemType *a = new ItemType(*count->pItem);
        head->pItem = a;
        Node *current = head;
        count = count->next;

        bool objRemaining = true;
        while (objRemaining)
        {

            if (count->next == NULL)
            {

                objRemaining = false;
                Node *n = new Node();
                ItemType *a = new ItemType(*count->pItem);
                n->pItem = a;
                current->next = n;
            }
            else
            {
                Node *n = new Node();
                ItemType *a = new ItemType(*count->pItem);
                n->pItem = a;
                current->next = n;
                current = current->next;
                count = count->next;
            }
        }
    }
    return *this;
}

template <class ItemType>
bool LinkedList<ItemType>::operator==(LinkedList<ItemType> const &obj) const
{
    Node *currentThis = head;
    Node *currentObj = obj.head;
    bool objectRemaining = true;
    // check if both lists are empty, return true and abort if both lists are empty.
    if (currentThis->pItem == NULL && currentObj->pItem == NULL)
    {
        return true;
    }

    // if only one of the lists are empty, return false
    else if (currentThis != NULL && currentObj == NULL)
    {
        return false;
    }
    else if (currentThis == NULL && currentObj != NULL)
    {
        return false;
    }

    // both lists have objects, compare both of them
    while (objectRemaining)
    {
        if (*currentThis->pItem != *currentObj->pItem)
        {
            // if one element is different from the other, then it muct mean they have different elements
            return false;
        }
        if (currentThis->next == NULL && currentObj->next == NULL)
        {
            // if both lists ended without triggering the above condition, they must have same elements
            return true;
        }
        else if (currentThis->next == NULL || currentObj->next == NULL)
        {
            // if one list reaches its end while the other does not, it must not have same amount of elements
            return false;
        }
        else
        {
            currentThis = currentThis->next;
            currentObj = currentObj->next;
        }
    }
    return false;
}

template <class ItemType>
bool LinkedList<ItemType>::operator!=(LinkedList<ItemType> const &obj) const
{
    if (*this == obj)
    {
        return false;
    }
    else
    {
        return true;
    }
}
#endif

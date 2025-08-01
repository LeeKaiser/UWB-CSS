#include "LinkedListV1.h"
#ifndef LinkedListV1_CPP
#define LinkedListV1_CPP

template <class ItemType>
LinkedList<ItemType>::LinkedList() {}

template <class ItemType>
LinkedList<ItemType>::LinkedList(LinkedList<ItemType> &source)
{
    // currently shallow copy, change to deep copy later

    *this = source;
}
template <class ItemType>
bool LinkedList<ItemType>::Insert(ItemType *obj)
{
    ItemType *inputVar = new ItemType(*obj);
    if (head->pItem == NULL)
    {
        head->pItem = inputVar;
        return true;
    }
    
    //if smaller than head
    if (*head->pItem > *inputVar)
    {
        
        Node *x = new Node();
        x->pItem = inputVar;
        Node *y = new Node();
        y->pItem = head->pItem;
        y->next = head->next;
        x->next = y;
        head = x;

        return true;
    }
    //other cases
    Node *current = head;
    while (true)
    {
        

        // if current element is same as obj
        if (*inputVar == *current->pItem)
        {
            // cout << "case 1" << endl;
            return false;
        }
        // if comparing with last element and is larger
        else if (current->next == NULL && *inputVar > *current->pItem)
        {
            //cout << "case 2" << endl;
            Node *x = new Node();
            x->pItem = inputVar;
            current->next = x;
            return true;
        }
        // if invutVar is larger than current element but smaller than next item
        else if (*current->next->pItem > *inputVar && *inputVar > *current->pItem)
        {
            //cout << "case 3" << endl;
            Node *x = new Node();
            x->pItem = inputVar;
            x->next = current->next;
            current->next = x;
            return true;

        }
        // if is larger but there is next element
        else if (*inputVar > *current->pItem)
        {
            //cout << "case 4" << endl;
            current = current->next;
        }
        else
        {
            cout << "there must be a case that has not been factored" << endl;
            return false;
        }
    }
    cout << "there has been a problem" << endl;
    return false;
}

template <class ItemType>
bool LinkedList<ItemType>::Remove(ItemType target, ItemType &result)
{

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
            head->pItem = NULL;
        }
        else
        {
            head = head->next;
            delete current;
            current = nullptr;
        }
        
        
        return true;
    }

    Node *previous;

    while(true)
    {
        
        //when element other than first is detected to be removed
        if (*current->pItem == target)
        {
            result = *current->pItem;
            previous->next = current->next;
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
    Node *current = head;
    
    while(true)
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
    while (head->pItem != NULL)
    {
        ItemType x;
        Remove(*head->pItem,x);
    }
}

template <class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    if (head->pItem == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif

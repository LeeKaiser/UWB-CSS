#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>
#include <fstream>
using namespace std;

template <class ItemType>
class LinkedList
{
    
public:
    LinkedList();
    LinkedList(LinkedList<ItemType> const &);
    ~LinkedList();

    bool BuildList(string fileName);

    bool Insert(ItemType *obj);

    bool Remove(ItemType target, ItemType &result);

    bool Peek(ItemType target, ItemType &result) const;

    bool isEmpty() const;

    void DeleteList();

    bool Merge(LinkedList &list1);

    LinkedList operator+(LinkedList const &obj) const;

    LinkedList &operator+=(LinkedList const &obj);

    bool operator==(LinkedList const &obj) const;
    bool operator!=(LinkedList const &obj) const;

    LinkedList &operator=(LinkedList const &obj);

    friend ostream &operator<<(ostream &os, const LinkedList<ItemType> &obj)
    {
        Node *current = obj.head;
        bool done = false;
        while (!done)
        {
            if (current->pItem == NULL)
            {
                return os;
            }
            os << *current->pItem;
            if (current->next == NULL)
            {
                done = true;
            }
            else
            {
                current = current->next;
            }
        }
        return os;
    }

private:
    struct Node
    {
        ItemType *pItem = nullptr;
        Node *next = nullptr;

    };
    Node* head = new Node();

};

#include "LinkedList.cpp"
#endif
//file bintree.h
//for assignment 2 CSS 343
//Kaiser Lee

#include <iostream>
using namespace std;
#include "nodedata.h"

//---------------------------------------------------------------------------
// bintree is a binary tree holding NodeData. it is sorted to perform 
// binary search. 
// elements in the binary tree are automatically sorted. 
//
// Implementation and assumptions:
// duplicates are not valid and they are ignored
// the tree is always sorted to have lowest elements in left and highest 
// elements in right. 
// insert puts the elements in the BinTree.
// overloads =, ==, and != operators
//
//---------------------------------------------------------------------------

class BinTree { 

friend ostream& operator<<(ostream&, const BinTree&); // print out tree 

public:
    BinTree();  //constructor
    BinTree(const BinTree &);   //copy constructor
    ~BinTree(); // calls makeEmpty()
    

    BinTree& operator=(const BinTree &);    //set this as other
    bool operator==(const BinTree &) const; //check if equals
    bool operator!=(const BinTree &) const; //inverse of ==

    bool isEmpty() const; //return true if no elements
    void makeEmpty(); // delete all memory so isEmpty() returns true
    bool insert(NodeData*); //insert element to the list. 
    bool retrieve(const NodeData&, NodeData*&) const; // retrieves elements
    bool remove(const NodeData &, NodeData*&); // remove elements
    void displaySideways() const; // displays the tree sideway
    bool getSibling(const NodeData&, NodeData&) const; //finds sibling node
    bool getParent(const NodeData&, NodeData&) const;   //finds parent node
    void bstreeToArray(NodeData* []);   //fill array using a bs tree
    void arrayToBSTree(NodeData* []);   //fill bs tree using array
    

private:
    struct Node {
        NodeData* data; // pointer to data object
        Node* left; // left subtree pointer
        Node* right; // right subtree pointer
    };
    Node* root; // root of the tree
    // utility functions
    // recursive helper for operator<<
    void inOrderHelper( Node*) const; // helper function for << operator
    void sidewaysHelper(Node*, int) const; // helper function display sideways
    void makeEmptyHelper(Node*); // helper function for make empty
    Node* copyRecursive ( Node*); // copies info from other into this
    bool findFalse(const Node*, const Node*) const; // helper function for ==
    // helper function for retrieve
    bool retrieveHelper(const NodeData&, NodeData*&, const Node*) const;
    // helper function for remove
    bool removeHelper(const NodeData&, NodeData*&, Node*&);
    void deleteCurrent(Node*& current); // helper function for remove
    NodeData* findPredAndDelete(Node*&);// helper function for remove
    // helper function for getSibling
    bool getSiblingHelper(const NodeData&, NodeData&, Node*) const;
    // helper function for getParent
    bool getParentHelper(const NodeData&, NodeData&, Node*) const;
    // helper function for bsTreeToArray
    void bsTreeToArrayHelper(Node*&, NodeData* [],int &);
    // helper function for arrayToBSTree
    void arrayToBSTreeHelper(Node*&, NodeData* [], int min, int max);

};
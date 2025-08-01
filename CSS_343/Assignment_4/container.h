//---------------------------------------------------------------------------
// container.h - Kaiser Lee
//---------------------------------------------------------------------------
// Container that holds a bintree of media objects. 
//
// Assumptions:
// a container object will be dedicated to storing one type of media
//---------------------------------------------------------------------------
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
using namespace std;
#include "media.h"
class PubInfo;

class Container { 

friend ostream& operator<<(ostream&, const Container&); // print out tree 

public:
    Container();  //constructor
    Container(const Container &);   //copy constructor
    ~Container(); // calls makeEmpty()
    

    //Container& operator=(const Container &);    //set this as other
    //bool operator==(const Container &) const; //check if equals
    //bool operator!=(const Container &) const; //inverse of ==

    bool isEmpty() const; //return true if no elements
    void makeEmpty(); // delete all memory so isEmpty() returns true
    bool insert(Media*); //insert element to the list. 
    bool retrieve(const PubInfo&, Media*&) const; // retrieves elements
    bool remove(const Media &, Media*&); // remove elements
    void displaySideways() const; // displays the tree sideway
    //bool getSibling(const Media&, Media&) const; //finds sibling node
    //bool getParent(const Media&, Media&) const;   //finds parent node
    //void bstreeToArray(Media* []);   //fill array using a bs tree
    //void arrayToBSTree(Media* []);   //fill bs tree using array
    

private:
    struct Node {
        Media* data; // pointer to data object
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
    bool retrieveHelper(const PubInfo&, Media*&, const Node*) const;
    // helper function for remove
    bool removeHelper(const Media&, Media*&, Node*&);
    void deleteCurrent(Node*& current); // helper function for remove
    Media* findPredAndDelete(Node*&);// helper function for remove
    // helper function for getSibling
    //bool getSiblingHelper(const Media&, Media&, Node*) const;
    // helper function for getParent
    //bool getParentHelper(const Media&, Media&, Node*) const;
    // helper function for bsTreeToArray
    //void bsTreeToArrayHelper(Node*&, Media* [],int &);
    // helper function for arrayToBSTree
    //void arrayToBSTreeHelper(Node*&, Media* [], int min, int max);

};

#endif
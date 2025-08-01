//file intset.h
//for assignment 1 CSS 343
//Kaiser Lee

#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
//int set holds ints using bool array, where if it is holding a certain
//value, then it sets the bool at that value as true, false otherwise.
//
// Implementation and assumptions:
// Valid values are positive ints (and 0), invalid values are ignored
//
//
//---------------------------------------------------------------------------

class IntSet {

// overloaded <<: print IntSet. only the true values. 
//  Display { 5 10 12 20 25 100} to represent the set containing the integers
//  5, 10, 12, 20, 25, and 100. The empty set is displayed exactly as: {}
    friend ostream& operator<<(ostream&, const IntSet&);

// overloaded >>: Input entire set. loop to take ints
//  terminate at -1. ignore invalid ints.
    friend istream& operator>>(istream&, IntSet&);

    public:
        // constructors & destructors
        IntSet (int Val1 = -1, int Val2 = -1, int Val3 = -1, int Val4 = -1, 
            int Val5 = -1);                         // constructor
        IntSet (const IntSet&);                     // copy constructor
        ~IntSet ();                                 // destructor

        // operator overloads
        IntSet operator+(const IntSet &) const;     // Union operator
        IntSet operator-(const IntSet &) const;     // in one but not other
        IntSet operator*(const IntSet &) const;     // Intersection
        IntSet& operator+=(const IntSet &);          // Union
        IntSet& operator-=(const IntSet &);          // in one but not other
        IntSet& operator*=(const IntSet &);          // Intersection
        IntSet& operator=(const IntSet &);    // assignment operator
        bool operator==(const IntSet &) const;      // equals operator
        bool operator!=(const IntSet &) const;      // not equals overator

        // Methods
        bool insert(const int&);                //add element to list
        bool remove(const int&);                //remove element
        bool isEmpty();                         //return true if no element
        bool isInSet(const int&) const;               //return true if in set
        bool isValid(const int&) const;               //check if input is valid
        void increaseSize(const int&);          //increases size of array
    
    private:
        //private variables
        bool* arrayPtr;                         // pointer to array
        int size;                               // size of array

};

#endif
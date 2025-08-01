#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&); // build the tree using given data file
void initArray(NodeData* []);        // initialize an array elements to nullptr

int main() {
   // create file object infile and open it
   // for testing, call your data file something appropriate, e.g., data2.txt
   ifstream infile("quest1.txt");
   if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // the NodeData class must have a constructor that takes a string
   NodeData notND("not");
   NodeData andND("tttt");
   NodeData sssND("sss");
   NodeData eND("e");
   NodeData mND("m");
   NodeData tND("t");

   BinTree T, T2, dup;
   NodeData* ndArray[ARRAYSIZE];
   initArray(ndArray);
   cout << "Initial data:" << endl << "  ";
   buildTree(T, infile);              // builds and displays initial data

   NodeData nd;                    // copy of either sibling or parent
      NodeData notFound("notFound");
      bool success = false;
   success = T.getParent(andND, nd);
    cout << "Parent of tttt:  " << (success ? nd : notFound) << endl;
    T.displaySideways();
    //initArray(ndArray);


}

//----------------------------------------------------------------------------
// buildTree
//
// To build a tree, read strings from a line, terminating with "$$" .
// Since there is some work to do before the actual insert that is specific to 
// the client problem (tree class does not know about the data that it holds), 
// building a tree is not a member function.  It's a global function. 

void buildTree(BinTree& t, ifstream& infile) {
   string s;

   for (;;) {
      infile >> s;
      cout << s << ' ';
      if (s == "$$") {                      // at end of one line
         break;                
      }

      // no more lines of data, must attempt to read the line so the
      // end-of-file character is read, triggering eof() to be true
      if (infile.eof()) {                   
         break;             
      }

      // in an object-oriented program, change to setData() for reading 
      NodeData* ptr = new NodeData(s);     

      bool success = t.insert(ptr);   
      if (!success) {
         delete ptr;                       // duplicate case, not inserted 
         ptr = nullptr;
      }
   }
}

//----------------------------------------------------------------------------
// initArray 
// initialize the array of NodeData* to hold nullptr 

void initArray(NodeData* ndArray[]) {
   for(int i = 0; i < ARRAYSIZE; i++) {
      ndArray[i] = nullptr;
   }
}
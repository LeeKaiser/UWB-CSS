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
   ifstream infile("data2.txt");
   if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // the NodeData class must have a constructor that takes a string
   NodeData notND("not");
   NodeData andND("and");
   NodeData sssND("sss");
   NodeData eND("e");
   NodeData mND("m");
   NodeData tND("t");

   BinTree T, T2, dup;
   NodeData* ndArray[ARRAYSIZE];
   initArray(ndArray);
   cout << "Initial data:" << endl << "  ";
   buildTree(T, infile);              // builds and displays initial data
   buildTree(T2,infile);
   cout << endl; 
   cout << "Tree Inorder:" << endl << T;             // operator<< does endl
   cout << endl;
    T.displaySideways();
    cout << endl;
    BinTree T3(T);
    cout << "T3 inorder:" << endl << T3 << endl;
    T3.displaySideways();
    cout << "T2 Inorder:" << endl << T2 << endl;             // operator<< does endl
    cout << "T3 == T: " << (T3 == T)  << endl;
    cout << "T2 == T: " << (T2 == T)  << endl;
    cout << "set T2 to be T3" << endl;
    T2 = T3;
    cout << "T2 Inorder:" << endl << T2 << endl; 
    NodeData* x; 
    cout << "Tree Inorder:" << endl << T << endl; 
    cout << "retrieve not from T: " << T.retrieve(notND, x) << *x << endl;
    cout << "retrieve e from T: " << T.retrieve(eND, x) << endl;
    cout << "retrieve and from T: " << T.retrieve(andND, x) << *x << endl;
    NodeData y;
    cout << "Tree Inorder:" << endl << T << endl; 
    cout << "getSibling not from T: " << T.getSibling(notND, y) << y << endl;
    cout << "Tree Inorder:" << endl << T << endl; 
    cout << "getSibling e from T: " << T.getSibling(eND, y) << endl;
    cout << "Tree Inorder:" << endl << T << endl; 
    cout << "getParent not from T: " << T.getParent(notND, y) << y << endl;
    cout << "Tree Inorder:" << endl << T << endl; 
    cout << "getParent e from T: " << T.getParent(eND, y) << endl;
    cout << "remove not from T: " << T.remove(notND, x) << *x << endl;
    delete x;
    cout << "remove m from T: " << T.remove(mND, x) << *x << endl;
    delete x;
    T.bstreeToArray(ndArray); //test this tomorrow
    for (int i = 0; i < 100; i ++)
    {
      if (ndArray[i] == nullptr)
      {
         i = 100;
      }
      else
      {
         cout << *ndArray[i] << " ";
      }
    } 
    
    cout << endl << "Tree is empty: " << T.isEmpty() << endl;
    T.arrayToBSTree(ndArray);
    for (int i = 0; i < 100; i ++)
    {
      if (ndArray[i] == nullptr)
      {
         i = 100;
      }
      else
      {
         cout << *ndArray[i] << " ";
      }
    } 
    cout << endl << "Tree filled: " << endl;
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

// container.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "container.h"
#include "pubInfo.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// create an empty binary tree
Container::Container()
{
   //set root at nullptr to avoid errors
   root = nullptr;
}

//---------------------------------------------------------------------------
// Copy Constructor
// create an empty binary tree
Container::Container(const Container &other)
{
   //use copy method
   root = copyRecursive(other.root);
}

//---------------------------------------------------------------------------
// Destructor
// delete this tree
Container::~Container()
{
   //use makeEmpty to delete everything in bin tree
   makeEmpty();
}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// Insert
// accept Media object then inserts it to the appropriate section in 
// the binary tree
// using modified version of the class notes insert function
bool Container::insert(Media* dataptr)
{
   Node* ptr = new Node;
   if (ptr == nullptr) return false;                // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = nullptr;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                     // walking pointer
      bool inserted = false;                    // whether inserted yet

      // Traverse tree; if item is less than current item, insert in 
      // left subtree, otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == nullptr) {     // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;         // one step left
         }
         else if (*ptr->data > *current->data){
            if (current->right == nullptr) {    // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;        // one step right
         } else { // ==          when there is duplicate
            current->data->addCopies();
            delete ptr;
            ptr = nullptr;
            return false;
         }
      }
   }
   return true;
}

//---------------------------------------------------------------------------
// retrieve & retrieveHelper
// looks through the binary tree to find if a Media object is in the 
// binary tree. returns true if found, false otherwise. 
// sets accept as the data if found.
bool Container::retrieve(const PubInfo&find , Media*&accept ) const
{
   
   return retrieveHelper(find, accept, root);
}

//---------------------------------------------------------------------------
// retrieveHelper
// loop through the bin tree to find the element being sought
// find is the element it is looking for
// set accept to data found and return true
// return false if not found (reached nullptr)
// go down to left or right element depending on if the element being sought
// is larger or smaller
bool Container::retrieveHelper(const PubInfo& find, Media*& accept, 
   const Node* current) const
{
   if (current == nullptr) // reached nullptr because couldn't find element
   {
      return false;  //return false (ends recursion)
   }
   if (current->data->compareToPubInfo(find)) // found the data
   {
      
      accept = current->data; //set accept to current
      return true;   //return true (ends recursion)
   }
   else // not at end but did not find element yet
   {
      //when current data is greater than find, search left
      if (current->data->compareToPubInfoGreaterThan(find)) 
      {
         return retrieveHelper(find, accept, current->left);
      }
      //when current data is less than find, search right
      else
      {
         return retrieveHelper(find, accept, current->right);
      }
   }
   return false; //should not reach this
}

//---------------------------------------------------------------------------
// remove & removeHelper & deleteCurrent & findPredAndDelete
// if it finds the element being sought (find), then sets accept to it and
// removes it from the list.
// using modified version of the class sample remove function
bool Container::remove(const Media &find, Media*&accept)
{
   return removeHelper(find, accept, root);
}
//---------------------------------------------------------------------------
// removeHelper
bool Container::removeHelper(const Media&find , Media*&accept, 
   Node*&current)
{
   
   // tree or subtree is empty
   if (current == nullptr) {
      return false;
   }

   // found item to remove
   if (find == *current->data) {
      accept = current->data;
      deleteCurrent(current);
      return true;
   }
   if (find < *current->data) {                      // search left subtree
      return removeHelper(find,accept,current->left);
   }

   // target >= *current->data                         // search right subtree
   return removeHelper(find,accept,current->right);
}

//----------------------------------------------------------------------------
// deleteCurrent
// contains all ways to delete data in bin tree
void Container::deleteCurrent(Node*& current) {
   // current has no children
   if (current->left == nullptr && current->right == nullptr) {
      //delete current->data;
      current->data = nullptr;
      delete current;
      current = nullptr;
   }

   // current has only right child
   else if (current->left == nullptr) {
      Node* temp = current;
      current = current->right;
      //delete temp->data;
      temp->data = nullptr;
      delete temp;
      temp = nullptr;
   }

   // current has only left child
   else if (current->right == nullptr) {
      Node* temp = current;
      current = current->left;
      //delete temp->data;
      temp->data = nullptr;
      delete temp;
      temp = nullptr;
   }

   // current has two children
   else {
      //delete current->data;
      current->data = nullptr;
      //deletes predecessor
      current->data = findPredAndDelete(current->left);
   }
}

//---------------------------------------------------------------------------
// findPredAndDelete
// finds the predecessor of current in deleteCurrent then has its Media
// replace the data of current.
//assumes it puts in left of current in the helper 
Media* Container::findPredAndDelete(Node*& current)
{
   //if there is nothing on right
   if (current->right == nullptr) {
      //cout << *current->data << endl;
      Media* item = current->data; //returns this
      current->data = nullptr;
      Node* junk = current; 
      current = current->left; //sets current to be its left node
      delete junk;// delete node that had predecessor
      junk = nullptr;
      return item;
   }
   //traverse through right
   return findPredAndDelete(current->right);
}

/* //---------------------------------------------------------------------------
// getSibling & getSiblingHelper
// sets accept as the sibling of find, then returns true
// if the find does not have sibling or find does not exist in bin tree, 
// returns false
bool Container::getSibling(const Media& find, Media& accept) const
{
   return getSiblingHelper(find, accept, root); //use helper
}

//---------------------------------------------------------------------------
// getSiblingHelper
// returns sibling if one of the child node is found to have the value
// the user is seeking (find)
bool Container::getSiblingHelper(const Media& find, Media& accept, 
   Node* current) const
{
   if (current == nullptr) // reached nullptr because couldn't find element
   {
      return false;  //return false (ends recursion)
   } 
   if (current -> left != nullptr && current->right != nullptr)
   {
      if (*current->left->data == find) // found the data in left
      {
         accept = *current->right->data; //set accept as right
         return true;   //return true (ends recursion)
      }
      else if (*current->right->data == find) // found the data in right
      {
         accept = *current->left->data; //set accept as left
         return true;   //return true (ends recursion)
      }
   }
   
   //when find is greater than current data, search right
   if (find > *current->data) 
   {
      return getSiblingHelper(find, accept, current->right);
   }
   //when find is less than current data, search left
   else //if (find < *current->data) 
   {
      return getSiblingHelper(find, accept, current->left);
   }
   
   return false; //should not reach this
}

//---------------------------------------------------------------------------
// getParent & getParentHelper
// sets accept as the parent of find, then returns true
// if the find does not exist or is the root, returns false
bool Container::getParent(const Media&find, Media&accept) const
{
   return getParentHelper(find,accept,root);
}

//---------------------------------------------------------------------------
// getParentHelper
// returns data at current if one of the child is found to have the data
// the user is seeking (find)
bool Container::getParentHelper(const Media& find, Media& accept, 
   Node* current) const
{
   // reached nullptr because couldn't find element or element at root
   if (current == nullptr || *current->data == find) 
   {
      //cout << "reached end";
      return false;  //return false (ends recursion)
   }   
   // found the data
   if (current->left != nullptr)
   {
      if (*current->left->data == find)
      {
         accept = *current->data; //set accept as right
         return true;   //return true (ends recursion)
      }
   }
   if (current->right != nullptr)
   {
      if (*current->right->data == find)
      {
         accept = *current->data; //set accept as right
         return true;   //return true (ends recursion)
      }
   }
    // not at end but did not find element yet
   
   //when find is greater than current data, search right
   if (find > *current->data) 
   {
      //cout << "going right, currently at " << *current->data ;
      return getParentHelper(find, accept, current->right);
   }
   //when find is less than current data, search left
   else //if (find < *current->data) 
   {
      //cout << "going left, currently at " << *current->data ;
      return getParentHelper(find, accept, current->left);
   }
   
   return false; //should not reach this
}

//---------------------------------------------------------------------------
// BSTreeToArray & bsTreeToArrayHelper
// puts all the contents of this bs tree into the array put in the parameter.
// leaves the tree empty
void Container::bstreeToArray(Media* arr[])
{
   // keeps track of where the element should be inserted
   int index = 0; 
   bsTreeToArrayHelper(root, arr,index);
   root = nullptr;
}
//---------------------------------------------------------------------------
// bsTreeToArrayHelper
void Container::bsTreeToArrayHelper(Node*& current, Media* arr[], int &index)
{
   //stop when reaching edge of Container
   if (current != nullptr)
   {
      //put left of tree
      bsTreeToArrayHelper(current->left,arr, index);
      //put current node
      arr[index] = current->data;
      current->data = nullptr;
      index ++;   //increase index to insert next element on correct spot
      //put right of tree
      bsTreeToArrayHelper(current->right,arr, index);
      //leave tree empty
      delete current;

   }
   
}

//---------------------------------------------------------------------------
// arrayToBSTree & arrayToBSTreeHelper
// puts the contents of the array in the parameter into  this binary tree. 
// leaves the array empty
void Container::arrayToBSTree(Media* arr[])
{
   //find length of array
   int len = -1;
   for (int i = 0; i < 100; i++)
   {
      if (arr[i] == nullptr)
      {
         i = 100; //finish loop
      } else
      {
         len++;
      }
   }
   //use helper
   //cout << len;
   
   if (len > -1) //does nothing if no element in array.
   {
      makeEmpty();
      root = new Node();
      root->left = root->right = nullptr;
      arrayToBSTreeHelper(root, arr, 0,len);
   }
   
}
//---------------------------------------------------------------------------
// arrayToBSTreeHelper
void Container::arrayToBSTreeHelper(Node*& current, Media* arr[], 
   int min, int max)
{
   //get mid
   int mid = (max + min) / 2;
   //insert the middle element at current
   if (arr[mid] != nullptr)
   {
      current->data = arr[mid];
      //cout << *current->data << mid << endl; debug 
      arr[mid] = nullptr;
      //insert left side of array
      if (mid > min)
      {
         //cout << min<<mid << endl;
         current->left = new Node();
         current->left->left = current->left->right = nullptr;
         arrayToBSTreeHelper(current->left,arr,min,mid-1);
      }
   
      //insert right side of aray
      if (mid < max)
      {
         //cout << mid << max << endl;
         current->right = new Node();
         current->right->left = current->right->right = nullptr;
         arrayToBSTreeHelper(current->right,arr,mid+1,max);
      }
   }
   else{
      //when attempting to insert invalid element, delete the node that was
      //created for it, just in case it's nessecary
      delete current;
      current = nullptr;
   }
   
   
} */ //methods from previous lab

 //---------------------------------------------------------------------------
// inOrderHelper
// recursive function that is used to help with putting the Container 
// in an order. used to help << operator
void Container::inOrderHelper(Node* current) const
{
   if (current != nullptr)
   {
      //add left of tree via recursive call
      if (current->left != nullptr)
      {
         inOrderHelper(current -> left);
      }
      //add this data to the array
      cout << left << setw(current->data->getCopiesAvailMaxLen()) ;
      cout << current->data->getCopiesAvail();
      current->data->printInfo();
      //add right of tree via recursive call
      if (current->right != nullptr)
      {
         inOrderHelper(current -> right);
      }
   }
   
} 


//---------------------------------------------------------------------------
// isEmpty
// returns true if there is no value stored in the binary tree, false 
// otherwise
bool Container::isEmpty() const
{
   // no element in root should mean it's empty
   return root == nullptr;
}

//---------------------------------------------------------------------------
// makeEmpty & makeEmptyHelper
// delete all elements in the binary tree.
// helper is recursive function that deletes the child then the current node's
// data
void Container::makeEmpty()
{
   
      //if it's empty, no need to do anything
   if (!isEmpty())
   {
      makeEmptyHelper(root); // delete everything
      root = nullptr;
   }
}
//---------------------------------------------------------------------------
// makeEmptyHelper
void Container::makeEmptyHelper(Node* current)
{
   if (current != nullptr)
   {
      //cout << "Deleting" << current->data << endl;
      //delete all the left element
      makeEmptyHelper(current->left);
      //delete all the right element
      makeEmptyHelper(current->right);
      //delete data and node
      delete current->data;
      delete current;
   }
   else{
      //cout << "current is nullptr" << endl;
   }
  
}

//---------------------------------------------------------------------------
// copyRecursive
// copies all the info from other into this
// assumes slot has no data and is proper slot for the item in other
//slot is the Node space for this and other is node of other 
Container::Node* Container::copyRecursive (Node* other)
{
   if (other != nullptr)
   {
      Node* ptr = new Node; // copy other's data
      Media* nd = new Media(*other->data);
      ptr->data = nd;
      ptr->left = ptr->right = nullptr;

      ptr->left = copyRecursive(other->left); //copy data for left child
      ptr->right = copyRecursive(other->right);//copy data for right child
      
      return ptr;
   }
   else return nullptr;
  
}

/* //---------------------------------------------------------------------------
// displaySideways & sidewaysHelper
// Displays a binary tree as though you are viewing it from the side.
// Turn head 90 degrees counterclockwise (to the left) to see tree structure.
// Hard coded displaying to standard output.
void Container::displaySideways() const {
   sidewaysHelper(root, 0);
}

void Container::sidewaysHelper(Node* current, int level) const {
   if (current != nullptr) {
      level++;
      sidewaysHelper(current->right, level);

      // indent for readability, same number of spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "         ";
      }

      cout << *current->data << endl;        // display information of object
      sidewaysHelper(current->left, level);
   }
}

//---------------------------------------------------------------------------
// findFalse
// returns false if current and other is found to have different value. 
// returns true if this and all the childs are confirmed to be true.
bool Container::findFalse(const Node* current, const Node* other) const
{
   //check for cases where current or other is null
   //would happen when reaching the end of the tree
   if (current == nullptr && other == nullptr)
   {
      return true;
   }
   //when one is null and other isn't
   else if ( (current != nullptr && other == nullptr)
   || (current == nullptr && other != nullptr)) 
   {
      return false;
   }
   //cases where both are not null:
   //check if current != other (return false)
   if (*current->data != *other->data)
   {
      return false;
   }
   //check if left child returns true. return false otherwise
   if (!findFalse(current->left,other->left))
   {
      return false;
   }
   //check if right child returns true. return false otherwise
   if (!findFalse(current->right,other->right))
   {
      return false;
   }
   //every check to find possible cases of inequality has been done
   return true;
} */

//---------------------------------------------------------------------------
// overload operator
//---------------------------------------------------------------------------
// << operator overload
// print out the bin tree in order. 
ostream &operator<<(ostream &os, const Container &obj)
{
   obj.inOrderHelper(obj.root); //use helper to print out elements
   return os << endl; // puts endl at the end
}

/* //---------------------------------------------------------------------------
// = operator overload
// if this and other is not the same Container, copy other into this
Container& Container::operator=(const Container &other)
{
   if (*this == other)
   {
      return *this;
   }
   makeEmpty();
   root = copyRecursive(other.root);
   return *this;
}

//---------------------------------------------------------------------------
// == operator overload
// use findFalse to find any case where the two bin trees differ, 
// if there is no difference, returns true.
bool Container::operator==(const Container &obj) const
{
   return findFalse(root, obj.root); // uses helper
}

//---------------------------------------------------------------------------
// != operator overload
// the inverse operation of ==, returns true if there is difference between
// obj and this.
bool Container::operator!=(const Container &obj) const
{
   return !findFalse(root, obj.root); // uses helper
} */ // operators that is not planned to be used
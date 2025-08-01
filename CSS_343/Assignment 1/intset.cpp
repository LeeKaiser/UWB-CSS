// IntSet.cpp file
//for assignment 1 CSS 343
//Kaiser Lee

#include "intset.h"


//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// IntSet constructor 
// accepts any amount of inputs from 0 to 5. also acts as default constustor
IntSet::IntSet(int Val1, int Val2, int Val3, int Val4, int Val5)
{
    
    size = 0;  
    arrayPtr = new bool[size+1];                    //make the array
    remove(0);
    insert(Val1);                                   //Add contents to array
    insert(Val2);
    insert(Val3);
    insert(Val4);
    insert(Val5);
}

//---------------------------------------------------------------------------
// IntSet Destructor
// delete the allocated array
IntSet::~IntSet()
{
    
    delete [] arrayPtr;                             // delete array
    arrayPtr = nullptr;
    
}

//---------------------------------------------------------------------------
// IntSet copy constructor
// copy info of one array into this one
IntSet::IntSet (const IntSet& toCopy)
{
    size = toCopy.size;
    arrayPtr = new bool[size + 1];
    for (int i = 0; i <= size; i++)
    {
        arrayPtr[i] = toCopy.arrayPtr[i];
    }
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// IsValid
// Checks if the input is valid. (not negative and possibly other conditions)
bool IntSet::isValid(const int& input) const
{
    return input >= 0;
}

//---------------------------------------------------------------------------
// IncreaseSize
// changes the size of the array to match the input value
// assumption: the input is larger than current size.
void IntSet::increaseSize(const int& input)
{
    
    bool* tempPtr = new bool[input + 1];    // Make copy of current array   
    for (int i = 0; i <= input; i++) {      // make whole array is empty
        
        tempPtr[i] = false; 
    }
    for (int i = 0; i <= size; i++) {
        tempPtr[i] = arrayPtr[i]; 
    }
    size = input;                           // Change Size 
    delete[] arrayPtr;                      // replace current with copy
	arrayPtr = tempPtr;
}

//---------------------------------------------------------------------------
// insert
// sets the value in the array to true
// assumption: input is valid number
// if it is not valid, it returns false. returns true if successful.
bool IntSet::insert(const int& input)
{
    if (!isValid(input))                    //check if input is valid
    {
        return false;
    }
    if (input > size)                   //increase size if nessecary
    {
        increaseSize(input);
    }
    arrayPtr[input] = true;             //set appropriate value to true
    return true;
}

//---------------------------------------------------------------------------
// remove
// sets the value in the array to true
bool IntSet::remove(const int& input)
{
    if (!isValid(input) || input > size) //fail if input is not valid or 
    {                                    //couldn't be in the list.
        return false;
    }
    arrayPtr[input] = false;
    return true;
}

//---------------------------------------------------------------------------
// isInSet
// return true if in set, return false if not
bool IntSet::isInSet(const int& input) const
{
    if (!isValid(input) || input > size)    //input is invalid or too big
    {
        return false;
    }
    return arrayPtr[input];
    
}

//---------------------------------------------------------------------------
// isEmpty
// go through list and return false if there is something in list
bool IntSet::isEmpty()
{
    for (int i = 0; i <= size; i ++)
    {
        if (isInSet(i))
        {
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------
// Operator overloads
//---------------------------------------------------------------------------
// << operator
//  Display { 5 10 12 20 25 100} to represent the set containing the integers
//  5, 10, 12, 20, 25, and 100. The empty set is displayed exactly as: {}
ostream &operator<<(ostream &os, const IntSet &obj)
{
    os << "{";
    for (int i = 0; i <= obj.size; i ++)
    {
        //cout << obj.arrayPtr[i] << " ";
        if (obj.arrayPtr[i] == true)
        {
            os << " " << i ;
        }
    }
    os << "}";
    return os;
}

//---------------------------------------------------------------------------
// >> operator
//  Display { 5 10 12 20 25 100} to represent the set containing the integers
//  terminate at -1. ignore invalid ints.
istream &operator>>(istream& is, IntSet& obj)
{
    int input = 0;
    while (input != -1)                             //loop for inputs.
    {
        is >> input;
        obj.insert(input);
    }
    return is;
}

//---------------------------------------------------------------------------
// + operator
// return union of two IntSets
IntSet IntSet::operator+(const IntSet &other) const
{
    IntSet ret(other);
    for (int i = 0; i <= size; i++)
    {
        if (arrayPtr[i])
        {
            ret.insert(i);
        }
    }
    return ret;
}

//---------------------------------------------------------------------------
// += operator
// return union of two IntSets
IntSet &IntSet::operator+=(const IntSet &other)
{
    *this = *this + other;
    return *this;
}

//---------------------------------------------------------------------------
// * operator
// return intersection of two IntSets
// IntSet IntSet::operator*(const IntSet &other) const
// {
//     IntSet ret(other); // everything in other is in ret. remove items not in
//     for (int i = 0; i <= size; i++)                                   //this
//     {
//         if (ret.isInSet(i) && !arrayPtr[i]) //remove from set if not in this
//         {
//             ret.remove(i);
//         }
        
//     }
//     if (ret.size > size)  //if size of other is greater than this arr, 
//     {                      //remove all that is greater than this
//         for (int i = size + 1; i <= ret.size; i++)
//         {
            
//             ret.remove(i);
//         }

//     }
//     return ret;
// }

IntSet IntSet::operator*(const IntSet &other) const
{
    IntSet ret;
    for (int i = 0; i <= size; i++) //loop through array and insert if 
    {                               //equal 
        if (other.size < i)
        {

        }
        else if (arrayPtr[i] && other.arrayPtr[i])
        {
            ret.insert(i);
        }
    }
    return ret;
}

//---------------------------------------------------------------------------
// *= operator
// return union of two IntSets
IntSet &IntSet::operator*=(const IntSet &other)
{
    *this = *this * other;
    return *this;
}

//---------------------------------------------------------------------------
// - operator
// return values in this but not other
IntSet IntSet::operator-(const IntSet &other) const
{
    IntSet ret(*this); // everything in this is in ret. remove items that are 
    for (int i = 0; i <= size; i++)                                //in other
    {
        if (i <= other.size && (ret.isInSet(i) && other.arrayPtr[i])) 
        {
            ret.remove(i);          //remove item that is also in other
        }
        
    }
    return ret;
}

//---------------------------------------------------------------------------
// -= operator
// return union of two IntSets
IntSet &IntSet::operator-=(const IntSet &other)
{
    *this = *this - other;
    return *this;
}

//---------------------------------------------------------------------------
// = operator
// Assign the values of other to this list 
IntSet& IntSet::operator=(const IntSet& other)
{
    if (*this != other)         // check if it is same
    {
        size = other.size;
        delete[] arrayPtr;
        arrayPtr = new bool[size + 1];
        for (int i = 0; i <= size; i++)
        {
            arrayPtr[i] = other.arrayPtr[i];
        }
    }
    
    return *this;
}

//---------------------------------------------------------------------------
// == operator
// Check if all values of the list is same
bool IntSet::operator==(const IntSet &other) const
{
    
    for (int i = 0; i <= size; i++)
    {
        if (i > other.size && arrayPtr[i])  //when there is a value greater 
        {                                   //than the size of other in this 
            return false;                   //array
            //cout << "val greater than other" << endl;
        }
        if ( i <= other.size && (other.arrayPtr[i] != arrayPtr[i]) )
        {                                        //when inequality is found
            return false;
            //cout << "differing value"<< endl;
        }
    }
    if (other.size > size)           //if size of other is greater than this
    {
        for (int i = size + 1 ; i <= other.size ; i++)
        {
            if (other.arrayPtr[i])
            {                               //when there is a value greater                               
                return false;               //than the size of this in other
                //cout << "val greater than this"<< endl;
            }                               //array
        }
    }
    return true; //the two arrays should be equal at this point
    
    
}

//---------------------------------------------------------------------------
// != operator
// just give the opposite of == operator
bool IntSet::operator!=(const IntSet &other) const
{
    if (*this == other)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// publication.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "publication.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Publication::Publication()
{
    //fill in all variables
}

//---------------------------------------------------------------------------
// copy Constructor
// 
Publication::Publication(const Publication& other)
{
    this->author = other.getAuthor();
    this->title = other.getTitle();
    this->year = other.getYear();
    this->month = other.getMonth();
}

//---------------------------------------------------------------------------
// Destructor
// 
Publication::~Publication()
{

}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// print info
// print the information of the fiction publication
void Publication::printInfo()
{
	cout << getTitle() << " " << getAuthor() << " " << getYear() << endl; 
}

//---------------------------------------------------------------------------
// compareToPubInfo
// compares the pub info of the command to this to see if it is the pub that 
// the command is looking for (not intended to be used)
bool Publication::compareToPubInfo(PubInfo pI) const
{
	return true;
}
//---------------------------------------------------------------------------
// compareToPubInfoGreaterThan
// compares the pub info of the command to see if this is greater than what
// the command is looking for (not intended to be used)
bool Publication::compareToPubInfoGreaterThan(PubInfo pI) const
{
	return true;
}
//---------------------------------------------------------------------------
// PublicationgetPubType
// gets the publication type of the publicaton
char Publication::getPubType()
{
    return PUBLICATION_TYPE;
}

//---------------------------------------------------------------------------
// Operator Overload
//---------------------------------------------------------------------------
// == operator
// not intended for use
 bool Publication::operator==(const Media &other) const
{
    return true;
} 

//---------------------------------------------------------------------------
// > operator
bool Publication::operator>(const Media &other) const
{
    return true;
} 

//---------------------------------------------------------------------------
// < operator
bool Publication::operator<(const Media &other) const
{
    return true;   
}
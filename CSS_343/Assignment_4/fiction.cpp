// fiction.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "fiction.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Fiction::Fiction(string author, string title, int year)
{
    //fill in all variables
    this->author = author;
    this->title = title;
    this->year = year;
}

//---------------------------------------------------------------------------
// Copy Constructor
// 
Fiction::Fiction(const Fiction& other)
{
	this->author = other.getAuthor();
    this->title = other.getTitle();
    this->year = other.getYear();
}

//---------------------------------------------------------------------------
// Destructor
// 
Fiction::~Fiction()
{

}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// print info
// print the information of the fiction publication
void Fiction::printInfo()
{
	//author, title, year
	
	cout << left << setw(AUTHOR_MAX_LENGTH) << author;
	cout << left << setw(TITLE_MAX_LENGTH) << title;
	cout << right << setw(YEAR_MAX_LENGTH) << year;
	cout << endl;
}

//---------------------------------------------------------------------------
// compareToPubInfo
// compares the pub info of the command to this to see if it is the pub that 
// the command is looking for
bool Fiction::compareToPubInfo(PubInfo pI) const
{
	if (pI.getAuthor() == author && pI.getTitle() == title)
	{
		return true; //if information matches, return true, false otherwise
	} 
	return false;
}

//---------------------------------------------------------------------------
// compareToPubInfoGreaterThan
// compares the pub info of the command to see if this is greater than what
// the command is looking for
bool Fiction::compareToPubInfoGreaterThan(PubInfo pI) const
{
	//if author is greater or author is same and title is greater, 
    // return true. Otherwise return false.
	if (author > pI.getAuthor())
	{
		return true;
	}
	else if(author == pI.getAuthor() && title > pI.getTitle())
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------
// PublicationgetPubType
// gets the publication type of the publicaton
char Fiction::getPubType()
{
    return PUBLICATION_TYPE;
}

//---------------------------------------------------------------------------
// Operator Overload
//---------------------------------------------------------------------------
// == operator
// sorted by author, then title. if two are the same, it is considered same
bool Fiction::operator==(const Media &other) const
{
    if (author == other.getAuthor() && title == other.getTitle())
	{
		return true;
	}
	return false;

} 

//---------------------------------------------------------------------------
// > operator
 bool Fiction::operator>(const Media &other) const
{
    //if author is greater or author is same and title is greater, 
    // return true. Otherwise return false.
	if (author > other.getAuthor())
	{
		return true;
	}
	else if(author == other.getAuthor() && title > other.getTitle())
	{
		return true;
	}
	return false;

} 

//---------------------------------------------------------------------------
// < operator
 bool Fiction::operator<(const Media &other) const
{
    //if not greater or equals, return true, otherwise return false
	if (*this > other || *this == other )
	{
		return false;
	}
	return true;

} 

// ostream & operator<<(ostream & os, const Media & other)
// {
//     os << other.getAuthor() << " " << other.getTitle() << " " << other.getYear();
//     //os << " " << other.getMonth();
//     return os;
// }
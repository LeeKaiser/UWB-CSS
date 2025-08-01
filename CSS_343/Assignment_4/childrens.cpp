// childrens.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "childrens.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Childrens::Childrens(string author, string title, int year)
{
    //fill in all variables
    this->author = author;
    this->title = title;
    this->year = year;
}

//---------------------------------------------------------------------------
// Copy Constructor
// 
Childrens::Childrens(const Childrens& other)
{
	this->author = other.getAuthor();
    this->title = other.getTitle();
    this->year = other.getYear();
}

//---------------------------------------------------------------------------
// Destructor
// 
Childrens::~Childrens()
{

}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// print info
// print the information of the fiction publication
void Childrens::printInfo()
{
	//author, title, year
	cout << left << setw(TITLE_MAX_LENGTH) << title;
	cout << left << setw(AUTHOR_MAX_LENGTH) << author;
	cout << right << setw(YEAR_MAX_LENGTH) << year;
	cout << endl;
}
//---------------------------------------------------------------------------
// compareToPubInfo
// compares the pub info of the command to this to see if it is the pub that 
// the command is looking for
bool Childrens::compareToPubInfo(PubInfo pI) const
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
bool Childrens::compareToPubInfoGreaterThan(PubInfo pI) const
{
	//if author is greater or author is same and title is greater, 
    //return true. Otherwise return false.
	if (title > pI.getTitle())
	{
		return true;
	}
	else if(title == pI.getTitle() && author > pI.getAuthor())
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------
// PublicationgetPubType
// gets the publication type of the publicaton
char Childrens::getPubType()
{
    return PUBLICATION_TYPE;
}

//---------------------------------------------------------------------------
// compareToPubInfoGreaterThan
// compares the pub info of the command to see if this is greater than what
// the command is looking for


//---------------------------------------------------------------------------
// Operator Overload
//---------------------------------------------------------------------------
// == operator
// sorted by author, then title. if two are the same, it is considered same
bool Childrens::operator==(const Media &other) const
{
    if (author == other.getAuthor() && title == other.getTitle())
	{
		return true;
	}
	return false;


} 

//---------------------------------------------------------------------------
// > operator
 bool Childrens::operator>(const Media &other) const
{
    //if author is greater or author is same and title is greater, 
    //return true. Otherwise return false.
	if (title > other.getTitle())
	{
		return true;
	}
	else if(title == other.getTitle() && author > other.getAuthor())
	{
		return true;
	}
	return false;


} 

//---------------------------------------------------------------------------
// < operator
 bool Childrens::operator<(const Media &other) const
{
    //if not greater or equals, return true, otherwise return false
	if (*this > other || *this == other )
	{
		return false;
	}
	return true;

} 
/* 
ostream & operator<<(ostream & os, const Childrens & other)
{
    os << other.getAuthor() << " " << other.getTitle() << " " << other.getYear();
    //os << " " << other.getMonth();
    return os;
} */
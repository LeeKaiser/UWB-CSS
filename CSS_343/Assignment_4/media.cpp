// media.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "media.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Media::Media()
{
    //fill in all variables
}

//---------------------------------------------------------------------------
// Copy Constructor
// 
Media::Media(const Media& other)
{
    this->author = other.getAuthor();
    this->title = other.getTitle();
    this->year = other.getYear();
    this->month = other.getMonth();
}

//---------------------------------------------------------------------------
// Destructor
// 
Media::~Media()
{

}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// getAuthor
// accessor for author variable
string Media::getAuthor()const
{
    return author;
}

//---------------------------------------------------------------------------
// getTitle
// accessor for Title variable
string Media::getTitle()const
{
    return title;
}

//---------------------------------------------------------------------------
// getYear
// accessor for year variable
int Media::getYear()const
{
    return year;
}

//---------------------------------------------------------------------------
// getMonth
// accessor for month variable
int Media::getMonth()const
{
    return month;
}

//---------------------------------------------------------------------------
// addCopies
// increase the amount of copies that the library is holding
void Media::addCopies()
{
    copiesAvailable++;
}
//---------------------------------------------------------------------------
// removeCopies
// decrease the amount of copies that the library is holding.
// returns false if there are no copies that can be borrowed
bool Media::removeCopies()
{
    if (copiesAvailable > 0)
    {
        copiesAvailable--;
        return true;
    }
    return false;
    

}

//---------------------------------------------------------------------------
// print info
// print available information of this media
void Media::printInfo()
{
    cout << getAuthor() << " " << getTitle() << " " ;
    cout << getYear() << " " << getMonth() << endl;
}

//---------------------------------------------------------------------------
// compareToPubInfo
// compares the pub info of the command to this to see if it is the pub that 
// the command is looking for (not intended to be used)
bool Media::compareToPubInfo(PubInfo pI) const
{
	return true;
}
//---------------------------------------------------------------------------
// compareToPubInfoGreaterThan
// compares the pub info of the command to see if this is greater than what
// the command is looking for (not intended to be used)
bool Media::compareToPubInfoGreaterThan(PubInfo pI) const
{
	return true;
}

//---------------------------------------------------------------------------
// getCopiesAvail
// retrns copies available
int Media::getCopiesAvail()
{
    return copiesAvailable;
}

//---------------------------------------------------------------------------
// getCopiesAvailMaxLen
// retrns copies available
int Media::getCopiesAvailMaxLen()
{
    return AVAIL_MAX_LENGTH;
}

//---------------------------------------------------------------------------
// PublicationgetPubType
// gets the publication type of the publicaton
char Media::getPubType()
{
    return PUBLICATION_TYPE;
}

//---------------------------------------------------------------------------
// Operator Overload
//---------------------------------------------------------------------------
// == operator
// should not be used
bool Media::operator==(const Media &other) const
{
    return true;
}

//---------------------------------------------------------------------------
// > operator
// should not be used
bool Media::operator>(const Media &other) const
{
    return true;
}

//---------------------------------------------------------------------------
// < operator
// should not be used
bool Media::operator<(const Media &other) const
{
    return true;
}

/* ostream & operator<<(ostream & os, const Media & other)
{
    os << other.getAuthor() << " " << other.getTitle() << " " << other.getYear();
    os << " " << other.getMonth();
    return os;
} */


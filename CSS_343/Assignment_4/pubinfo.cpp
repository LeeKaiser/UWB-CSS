//pubinfo.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "pubInfo.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
PubInfo::PubInfo(string author , string title, 
        int year, int month)
{
    this->author = author;
    this->title = title;
    this->year = year;
    this->month = month;
}

PubInfo::PubInfo(const PubInfo& other)
{
    this->author = other.getAuthor();
    this->title = other.getTitle();
    this->year = other.getYear();
    this->month = other.getMonth();
}

//---------------------------------------------------------------------------
// Default destructor
// 
PubInfo::~PubInfo()
{

}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// getAuthor
// accessor for author variable
string PubInfo::getAuthor()const
{
    return author;
}

//---------------------------------------------------------------------------
// getTitle
// accessor for Title variable
string PubInfo::getTitle()const
{
    return title;
}

//---------------------------------------------------------------------------
// getYear
// accessor for year variable
int PubInfo::getYear()const
{
    return year;
}

//---------------------------------------------------------------------------
// getMonth
// accessor for month variable
int PubInfo::getMonth()const
{
    return month;
}

//---------------------------------------------------------------------------
// == operator
// return true if the two pub info holds same information
bool PubInfo::operator==(const PubInfo &other) const
{
    if (author == other.getAuthor() && title == other.getTitle() && 
        year == other.getYear() && month == other.getMonth())
        {
            return true;
        }
    return false;
}
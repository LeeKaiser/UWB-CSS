// periodical.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "periodical.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Periodical::Periodical(string title, int month, int year)
{
    //fill in all variables
    this->title = title;
    this->month = month;
    this->year = year;
    this->author = "";
}
//---------------------------------------------------------------------------
// Copy Constructor
// 
Periodical::Periodical(const Periodical & other)
{
	this->title = other.getTitle();
    this->year = other.getYear();
    this->month = other.getMonth();
}


//---------------------------------------------------------------------------
// Destructor
// 
Periodical::~Periodical()
{}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// print info
// print the information of the fiction publication
void Periodical::printInfo()
{
	//author, title, year
	cout << left << setw(YEAR_MAX_LENGTH) << year;
	cout << left << setw(MONTH_MAX_LENGTH) << month;
	cout << left << setw(TITLE_MAX_LENGTH) << title;
	
	cout << endl;
}

//---------------------------------------------------------------------------
// compareToPubInfo
// compares the pub info of the command to this to see if it is the pub that 
// the command is looking for
bool Periodical::compareToPubInfo(PubInfo pI) const
{
	if (pI.getMonth() == month && pI.getTitle() == title 
		&& pI.getYear() == year)
	{
		return true; //if information matches, return true, false otherwise
	} 
	return false;
}

//---------------------------------------------------------------------------
// compareToPubInfoGreaterThan
// compares the pub info of the command to see if this is greater than what
// the command is looking for
bool Periodical::compareToPubInfoGreaterThan(PubInfo pI) const
{
	//if author is greater or author is same and title is greater, 
    // return true. Otherwise return false.

    //the case where this has more years
	if (year > pI.getYear())
	{
		return true;
	}
    //the case where this has more months but not years
	else if(year == pI.getYear() && month > pI.getMonth())
	{
		return true;
	}
    //the case where the date is same but author is greater
    else if(year == pI.getYear() && month == pI.getMonth() && title > 
        pI.getTitle())
	{
		return true;
	}
    //when this is less than other
	return false;

}

//---------------------------------------------------------------------------
// PublicationgetPubType
// gets the publication type of the publicaton
char Periodical::getPubType()
{
    return PUBLICATION_TYPE;
}

//---------------------------------------------------------------------------
// Operator Overload
//---------------------------------------------------------------------------
// == operator
bool Periodical::operator==(const Media &other) const
{
    if (year == other.getYear() && month == other.getMonth() && title == 
        other.getTitle())
	{
		return true;
	}
	return false;

} 
//---------------------------------------------------------------------------
// > operator
bool Periodical::operator>(const Media &other) const
{
    //if author is greater or author is same and title is greater, 
    // return true. Otherwise return false.

    //the case where this has more years
	if (year > other.getYear())
	{
		return true;
	}
    //the case where this has more months but not years
	else if(year == other.getYear() && month > other.getMonth())
	{
		return true;
	}
    //the case where the date is same but author is greater
    else if(year == other.getYear() && month == other.getMonth() && title > 
        other.getTitle())
	{
		return true;
	}
    //when this is less than other
	return false;

}

//---------------------------------------------------------------------------
// < operator
bool Periodical::operator<(const Media &other) const
{
    //if not greater or equals, return true, otherwise return false
	if (*this > other || *this == other )
	{
		return false;
	}
	return true;

}

/* ostream & operator<<(ostream & os, const Periodical & other)
{
    os << other.getTitle() << " " << other.getYear();
    os << " " << other.getMonth();
    return os;
} */
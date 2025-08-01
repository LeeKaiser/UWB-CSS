//---------------------------------------------------------------------------
// media.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a piece of media that the library would like to store
//
// Assumptions:
// the media object is not used directly, but the children of media would be
// used instead.
//---------------------------------------------------------------------------
#ifndef MEDIA_H
#define MEDIA_H
#include <iomanip>
#include <iostream>
using namespace std;
#include "pubInfo.h"

class Media
{
    //friend ostream & operator<<(ostream &, const Media &);
public:
    //constructor & destructor
    Media();
    Media(const Media&);
    virtual ~Media();
    //methods
    // accessors
    string getAuthor() const;
    string getTitle()const;
    int getYear()const;
    int getMonth()const;
    int getCopiesAvail();
    int getCopiesAvailMaxLen();

    void addCopies(); // add copies of this media
    bool removeCopies(); // remove copies of this media
    
    virtual void printInfo(); //prints formatted information of media
    virtual bool compareToPubInfo(PubInfo pI) const;
    virtual bool compareToPubInfoGreaterThan(PubInfo pI) const;
    virtual char getPubType();

    //operator overloads
    virtual bool operator==(const Media &other) const;
    virtual bool operator>(const Media &other) const;
    virtual bool operator<(const Media &other) const;


protected:
    //private variables
    string author = "";
	string title = "";
	int year = 0;
	int month = 0;
    int copiesAvailable = 5;
    static const int TITLE_MAX_LENGTH = 40;
    static const int AUTHOR_MAX_LENGTH = 30;
    static const int YEAR_MAX_LENGTH = 6;
    static const int MONTH_MAX_LENGTH = 6;
    static const int AVAIL_MAX_LENGTH = 6;
    static const char PUBLICATION_TYPE = 'x';
    //private methods
};

#endif
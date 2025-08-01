//---------------------------------------------------------------------------
// publication.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a publication that the library would like to store. child of 
// media.
// This is here in case there is a need for future expansion where some
// other types of media is disctinct from publications.
// 
// Assumptions:
// this is just a parent class, not intended to be used by other members.  
//---------------------------------------------------------------------------
#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "media.h"

#include "pubInfo.h"
using namespace std;

class Publication : public Media
{
public:
    //constructor & destructor
    Publication();
    Publication(const Publication&);
    virtual ~Publication();

    //methods
    virtual void printInfo(); //prints information of publication
    virtual bool compareToPubInfo(PubInfo pI) const; //functions like == for pubInfo
    virtual bool compareToPubInfoGreaterThan(PubInfo pI) const; // > for pubInfo
    virtual char getPubType();
    //operator overloads
    bool operator==(const Media &other) const;
    bool operator>(const Media &other) const;
    bool operator<(const Media &other) const;


private:
    //private variables
    static const char PUBLICATION_TYPE = 'x';

    //private methods
};

#endif
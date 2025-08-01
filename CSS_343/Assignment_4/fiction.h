//---------------------------------------------------------------------------
// fiction.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a fiction publication that the library would like to store.
// child of publication
// Assumptions:
// the comparison operator is intended to only have other fiction objects as
// parameter
//---------------------------------------------------------------------------
#ifndef FICTION_H
#define FICTION_H

#include "publication.h"
using namespace std;

class Fiction : public Publication
{
    //friend ostream & operator<<(ostream &, const Media &);
public:
    //constructor & destructor
    Fiction(string author, string title, int year);
    Fiction(const Fiction& other);
    ~Fiction();

    //methods
    void printInfo();
    bool compareToPubInfo(PubInfo pI) const; 
    //compares information in pubInfo with itself
    bool compareToPubInfoGreaterThan(PubInfo pI) const;
    // > version of compare pub info
    char getPubType();
    //operator overloads
    bool operator==(const Media &other) const;
    bool operator>(const Media &other) const;
    bool operator<(const Media &other) const;


private:
    //private variables
    static const char PUBLICATION_TYPE = 'F';

    //private methods
};

#endif
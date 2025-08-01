//---------------------------------------------------------------------------
// periodical.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a periodical publication that the library would like to store.
// child of publication
// Assumptions:
// the comparison operator is intended to only have other periodical objects as
// parameter
//---------------------------------------------------------------------------
#ifndef PERIODICAL_H
#define PERIODICAL_H
#include "publication.h"
using namespace std;

class Periodical : public Publication
{
    //friend ostream & operator<<(ostream &, const Periodical &);
public:
    //constructor & destructor
    Periodical(string title, int month, int year);
    Periodical(const Periodical & other);
    ~Periodical();

    //methods
    void printInfo();
    bool compareToPubInfo(PubInfo pI) const;
    bool compareToPubInfoGreaterThan(PubInfo pI) const;
    char getPubType();
    //operator overloads
    bool operator==(const Media &other) const;
    bool operator>(const Media &other) const;
    bool operator<(const Media &other) const;


private:
    //private variables
    static const char PUBLICATION_TYPE = 'P';

    //private methods
};

#endif
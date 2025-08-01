//---------------------------------------------------------------------------
// childrens.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a childrens publication that the library would like to store.
// child of publication
// Assumptions:
// the comparison operator is intended to only have other childrens objects as
// parameter
//---------------------------------------------------------------------------
#ifndef CHILDRENS_H
#define CHILDRENS_H
#include "publication.h"
using namespace std;

class Childrens : public Publication
{
    //friend ostream & operator<<(ostream &, const Childrens &);
public:
    //constructor & destructor
    Childrens(string author, string title, int year);
    Childrens(const Childrens& other);
    ~Childrens();

    //methods
    void printInfo();
    bool compareToPubInfo(PubInfo pI)const;
    bool compareToPubInfoGreaterThan(PubInfo pI)const;
    char getPubType();
    //operator overloads
    bool operator==(const Media &other) const;
    bool operator>(const Media &other) const;
    bool operator<(const Media &other) const;


private:
    //private variables
    static const char PUBLICATION_TYPE = 'C';

    //private methods
};

#endif
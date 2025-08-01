//---------------------------------------------------------------------------
// pubInfo.h - Kaiser Lee
//---------------------------------------------------------------------------
// stores several information on publication to be used for comparison
// also used as a representation of a publication for clients
// Assumptions:
// 
//---------------------------------------------------------------------------
#ifndef PUBINFO_H
#define PUBINFO_H
#include <iostream>
using namespace std;

class PubInfo
{
public:
    PubInfo(string author = "", string title = "", 
        int year = 0, int month = 0);
    PubInfo(const PubInfo&);
    ~PubInfo();
    //methods
    string getAuthor() const;
    string getTitle()const;
    int getYear()const;
    int getMonth()const;
    //operator overloads
    bool operator==(const PubInfo &other) const;
private:
    string author = "";
	string title = "";
	int year = 0;
	int month = 0;
};

#endif
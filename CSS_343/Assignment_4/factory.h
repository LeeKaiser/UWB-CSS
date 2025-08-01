//---------------------------------------------------------------------------
// factory.h - Kaiser Lee
//---------------------------------------------------------------------------
// Factory class for building media objects and client objects
// currently configured to accept publication types of Fiction, Periodicals,
// and childrens
// Assumptions:
// 
//---------------------------------------------------------------------------
#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <fstream>
class Client;
class Media;
class Publication;
class Fiction;
class Childrens;
class Periodical;
class Command;
class CheckOut;
class Library;
#include "pubInfo.h"
using namespace std;


class Factory
{
public:
    // constructor & destructor
    Factory();
    ~Factory();

    // creates a media object using the info in first line in file
    Media* buildMedia( ifstream&) const; 
    // call to make a new media object of appropriate type
    // create a client with given information
    Client* buildClient(ifstream&) const;
    //builds client using information in file
    Command* buildCommand(ifstream&) const;
    //builds commands using information in file
    PubInfo* buildPubInfo(char pubType,ifstream&) const;
    void getCommandInfo(ifstream&, int&,char&,char&) const;
private:
};

#endif
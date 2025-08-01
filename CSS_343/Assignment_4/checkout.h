//---------------------------------------------------------------------------
// checkout.h - Kaiser Lee
//---------------------------------------------------------------------------
// a command that can be executed to check out a publication for a client
// child of command
// Assumptions:
// intended to be created by factory then executed right after.
//---------------------------------------------------------------------------
#ifndef CHECKOUT_H
#define CHECKOUT_H

#include "command.h"

#include "client.h"
#include "library.h"


class CheckOut : public Command
{

public:
    CheckOut(int cID, char pubType, char copyType, PubInfo* pI); // constructor
    ~CheckOut(); // destructor
    void execute(Library& lib); // execute to make a client check out a publication

    //accessors
    string getCommandName();
    PubInfo* getPubInfo();
    char getPubType();

private:
    int cID; //client's ID
    char pubType;
    char copyType;
    PubInfo* pubInfo;
    string commandName = "CheckOut";
};

#endif
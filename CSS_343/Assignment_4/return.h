//---------------------------------------------------------------------------
// return.h - Kaiser Lee
//---------------------------------------------------------------------------
// a command that can be executed to return a publication that has been 
// checked out.
// child of command
// Assumptions:
// 
//---------------------------------------------------------------------------
#ifndef RETURN_H
#define RETURN_H

#include "command.h"
#include "client.h"
#include "library.h"
#include "pubInfo.h"

class Return : public Command
{

public:
    Return(int cID, char pubType, char copyType, PubInfo* pI); // constructor
    ~Return(); // destructor
    void execute(Library& lib); //makes the client return the publication

    //accessors
    string getCommandName();
    PubInfo* getPubInfo();
    char getPubType();
private:
    int cID; //client's ID
    char pubType;
    char copyType;
    PubInfo* pubInfo;
    string commandName = "Return";
};

#endif
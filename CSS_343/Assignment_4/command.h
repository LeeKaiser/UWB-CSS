//---------------------------------------------------------------------------
// command.h - Kaiser Lee
//---------------------------------------------------------------------------
// a command that can be executed to make the library do a certain task.
//
// Assumptions:
//   
//---------------------------------------------------------------------------
#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <fstream>
#include "pubInfo.h"
class Library;


class Command
{

public:
    Command(); //constructor
    virtual ~Command(); // destructor
    //methods
    virtual void execute(Library& lib); //virtual execute command
    virtual string getCommandName(); //accessor for command's name
    virtual PubInfo* getPubInfo(); //accessor for publication information
    virtual char getPubType(); //accessor for publication type
private:
    int cID; //client's ID
    char pubType; //publication type
    char copyType;//the type of copy 
    PubInfo* pubInfo; //publication information
    string commandName = ""; //command's name (left blank)

};

#endif
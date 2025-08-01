//command.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "command.h"
#include "library.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Command::Command()
{
}

//---------------------------------------------------------------------------
// Destructor
// 
Command::~Command()
{

}

//---------------------------------------------------------------------------
// methods
//---------------------------------------------------------------------------
// execute
// virtual method for execute
void Command::execute(Library& lib){}

//---------------------------------------------------------------------------
// getCommandName
// gets the name of the command (for history to use)
string Command::getCommandName()
{
    return commandName;
}

//---------------------------------------------------------------------------
// getPubInfo
// gets the PubInfo (assumes it's used in a child of command that actually uses
// PubInfo)
PubInfo* Command::getPubInfo()
{
    return pubInfo;
}

//---------------------------------------------------------------------------
// getPubType
// gets the PubType (assumes it's used in a child of command that actually uses
// PubInfo)
char Command::getPubType()
{
    return pubType;
}


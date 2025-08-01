//---------------------------------------------------------------------------
// history.h - Kaiser Lee
//---------------------------------------------------------------------------
// a command that can be executed to check out a publication for a client
// child of command
// Assumptions:
//   
//---------------------------------------------------------------------------
#ifndef HISTORY_H
#define HISTORY_H

#include "command.h"
#include "client.h"
#include "library.h"

class History : public Command
{

public:
    History(int cID); // constructor
    ~History(); // destructor
    void execute(Library& lib); //prints checkout & return history of client
private:
    int cID; //client's ID
    //formatting information
    static const int COMMAND_NAME_MAX_LENGTH = 10;
    static const int CLIENT_ID_MAX_LENGTH = 6;
    static const int TITLE_MAX_LENGTH = 40;
    static const int AUTHOR_MAX_LENGTH = 30;
    static const int YEAR_MAX_LENGTH = 6;
    static const int MONTH_MAX_LENGTH = 6;
    static const int AVAIL_MAX_LENGTH = 6;
};

#endif
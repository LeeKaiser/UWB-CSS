//---------------------------------------------------------------------------
// display.h - Kaiser Lee
//---------------------------------------------------------------------------
// a command that can be executed to show contents of library
// child of command
// Assumptions:
//   
//---------------------------------------------------------------------------
#ifndef DISPLAY_H
#define DISPLAY_H

#include "command.h"
#include "library.h"

class Display : public Command
{

public:
    Display(); // constructor
    ~Display(); // destructor
    void execute(Library& lib); //execute to print out library
private:
    static const int TITLE_MAX_LENGTH = 40;
    static const int AUTHOR_MAX_LENGTH = 30;
    static const int YEAR_MAX_LENGTH = 6;
    static const int MONTH_MAX_LENGTH = 6;
    static const int AVAIL_MAX_LENGTH = 6;
};

#endif
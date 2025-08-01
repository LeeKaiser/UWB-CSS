//factory.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "factory.h"
#include "media.h"
#include "publication.h"
#include "fiction.h"
#include "childrens.h"
#include "periodical.h"
#include "client.h"
#include "command.h"
#include "checkout.h"
#include "display.h"
#include "return.h"
#include "history.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Factory::Factory(){}

//---------------------------------------------------------------------------
// Destructor
// 
Factory::~Factory(){}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// buildMedia
// 
Media* Factory::buildMedia( ifstream& infile) const
{
    try
    {
        //char code;

        //infile >> code;                   // reads code

        // get (and ignore) blank before author,
        // don't use if you want to keep the blank as part of the author
        char code;
        infile >> code; //get the code for the publication
        infile.get();     
        if (code == 'F') //fiction
        {
            string author;
            getline(infile, author, ',');    // input author, looks for comma terminator
   
            // get (and ignore) blank before title,
            // don't use if you want to keep the blank as part of the title
            infile.get();                     
            string title;
            getline(infile, title, ',');     // input title
            int year;
            infile >> year;                  // input year
            //cout << "Fiction " << author << " " << title << " " << year << endl;
            return new Fiction(author,title,year);
        } else if (code == 'C')//childrens
        {
            string author;
            getline(infile, author, ',');    // input author, looks for comma terminator
   
            // get (and ignore) blank before title,
            // don't use if you want to keep the blank as part of the title
            infile.get();                     
            string title;
            getline(infile, title, ',');     // input title
            int year;
            infile >> year;                  // input year
            //cout << "Childrens " << author << " " << title << " " << year << endl;
            return new Childrens(author,title,year);
        } else if (code == 'P') //periodical
        {
            string title;
            getline(infile, title, ',');    // input title, looks for comma terminator
            int month;
            infile >> month; //get month data
            infile.get();      
            int year;
            infile >> year; //get year data
            //cout << "Periodical " << title << " " << month << " " << year << endl;
            return new Periodical(title,month,year);
        }
        //the code was not valid, skip the line
        cout << "ERROR: invalid input for media generation" << endl;
        string x;
        getline(infile,x);
    }
    catch (exception e)
    {
        //when invalid input
        cout << "ERROR: invalid input for media generation" << endl;
        //the code was not valid, skip the line
        string x;
        getline(infile,x);
    }
    //when input was not valid, simply return empty media object that is 
    // treated like invalid input.
    return nullptr;
}

//---------------------------------------------------------------------------
// buildClient
// 
Client* Factory::buildClient(ifstream& infile) const
{
    try 
    {
        int cID; //client ID
        infile >> cID;
        infile.get();
        string firstName; //first name
        string lastName; //last name
        infile >> firstName;
        infile.get();
        infile >> lastName;
        return new Client(cID,firstName,lastName); //return client
    }
    catch(exception e)
    {
        //in event of error:
        cout << "ERROR: Invalid input for client generation" << endl;
        string x;
        getline(infile,x);
    }
    return nullptr;
}

//---------------------------------------------------------------------------
// buildPubInfo
// 
Command* Factory::buildCommand(ifstream& infile) const
{
    try
    {
        char code;
        infile >> code;
        if (code == 'C') // build a checkout command
        {
            
            int cID;
            char pubType;
            char copyType;
            getCommandInfo(infile,cID,pubType,copyType);
            //get the publication's data
            PubInfo* pI = buildPubInfo(pubType, infile);
            return new CheckOut(cID, pubType, copyType, pI);
        }
        else if (code == 'R') //build a return command
        {
            int cID;
            char pubType;
            char copyType;
            getCommandInfo(infile,cID,pubType,copyType);
            //get the publication's data
            PubInfo* pI = buildPubInfo(pubType, infile);
            return new Return(cID, pubType, copyType, pI);
        }
        else if (code == 'H') //build a history command
        {
            int cID;
            infile.get();
            infile >> cID;
            infile.get();
            return new History(cID);
        }
        else if (code == 'D') //build display command
        {
            infile.get();
            return new Display();
            
        }
        else
        {
            //invalid command request
            cout << "ERROR: Command not available" << endl;
            string x;
            getline(infile,x);
        }
    }
    catch(const std::exception& e)
    {
        //in event of error
        cout << "ERROR: Command not available" << endl;
        string x;
        getline(infile,x);
    }
    return nullptr;
}
//---------------------------------------------------------------------------
// buildPubInfo
// 
PubInfo* Factory::buildPubInfo(char pubType, ifstream& infile) const
{
    try
    {
        if (pubType == 'F') //configured for fiction
        {
            infile.get();
            string author;
            getline(infile, author, ','); //input author
            infile.get();                     
            string title;
            getline(infile, title, ',');     // input title
            infile.get(); //
            return new PubInfo(author,title); //return pubInfo
        }
        else if (pubType == 'C') //configured for childrens
        {
            infile.get();                     
            string title;
            getline(infile, title, ',');     // input title
            infile.get();
            string author;
            getline(infile, author, ','); //input author
            infile.get();
            return new PubInfo(author,title); //return pubInfo
        }
        else if (pubType == 'P') // configured for periodicals
        {
            infile.get();                     
            int year;
            infile >> year;     // input year
            infile.get();                     
            int month;
            infile >> month;     // input year
            infile.get();
            string title;
            getline(infile, title, ','); //input author
            infile.get();
            return new PubInfo("",title,year,month);
        }
    }
    catch(const std::exception& e)
    {
        //in event of error
        cout << "ERROR: Problem with publication information" << endl;
    }
    return nullptr;
    
}

void Factory::getCommandInfo(ifstream& infile, int& cID,char& pubType,
    char& copyType) const
{
    //get the client ID
    infile.get();
    infile >> cID;
    // get publication type
    infile.get();
    infile >> pubType;
    // get the copy type (which should just be H for now)
    infile.get();
    infile >> copyType;
}
//---------------------------------------------------------------------------
// client.h - Kaiser Lee
//---------------------------------------------------------------------------
// represents a client who would like to use library's services
//
// Assumptions:
// client does not check out more than publicationlistsize amount of 
// publications
//---------------------------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H
#include <iomanip>
#include <iostream>
using namespace std;
#include "command.h" 
#include "checkout.h"
#include "pubInfo.h"

class Client
{

public:
    Client(int cID, string firstName, string lastName); //constructor
    ~Client();//destructor

    //methods
    //accessor methods
    int getClientID();
    string getFirstName();
    string getLastName();
    int getCommandListSize(); 
    void checkOutPub(PubInfo* pub); //adds the pub to the list
    bool returnPub(PubInfo* pub); // rmeoves the pub from the list
    void addHistory(Command* cmd); //adds command to the list
    Command** getHistory(); //returns list of commands
    

private:
    int clientID; //client's ID
    string firstName; //client's first name
    string lastName; //client's last name
    static const int PRESET_COMMAND_LIST_SIZE = 50;
    int commandListSize = PRESET_COMMAND_LIST_SIZE;
    Command* commandList[PRESET_COMMAND_LIST_SIZE]; //history of commands
    int publicationListSize = PRESET_COMMAND_LIST_SIZE;
    PubInfo* publicationList[PRESET_COMMAND_LIST_SIZE]; //list of publications
    //publications that the client checked out
    static const char PUBLICATION_TYPE = 'x';
};

#endif
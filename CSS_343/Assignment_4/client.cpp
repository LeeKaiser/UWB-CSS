//client.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "client.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Client::Client(int cID, string firstName, string lastName)
{
    //get variables
    this->clientID = cID;
    this->firstName = firstName;
    this->lastName = lastName;
    //initialize publicationlist with nullptr to avoid errors
    for (int i = 0; i < publicationListSize; i++)
    {
        //set all values in publication list as nullptr
        publicationList[i] = nullptr;
    }
    //initialize commandlist with nullptr to avoid errors
    for (int i = 0; i < commandListSize; i++)
    {
        //set all values in publication list as nullptr
        commandList[i] = nullptr;
    }
}

//---------------------------------------------------------------------------
// Default destructor
// 
Client::~Client()
{
	//delete publist
	for (int i = 0; i < publicationListSize ; i++)
    {
        if (publicationList[i] == nullptr)
        {
            
        }
        else{
            delete publicationList[i];
        }
        
    }

    //delete command list
	for (int i = 0; i < commandListSize ; i++)
    {
        if (commandList[i] == nullptr)
        {
            
        }
        else{
            delete commandList[i];
        }
        
    }
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// getClientID
// Accessor for client ID
int Client::getClientID()
{
    return clientID;
}

//---------------------------------------------------------------------------
// CheckOutPub
// adds a publication info to the publication list
void Client::checkOutPub(PubInfo* pub)
{
    for (int i = 0; i < publicationListSize; i++)
    {
        if (publicationList[i] == nullptr)
        {
            //add to the earliest nullptr
            publicationList[i] = pub;
            break;
            
        }
    }
    //if there is no space left, increase size by 1 and add publication to it
    //does not work for some reason. so client currently cannot store more than
    //PublicationListSize    
    /* PubInfo* largerPList[publicationListSize + 1];
    for (int i = 0; i < publicationListSize; i++)
    {
        //copy the content of old list to new list and delete element
        largerPList[i] = publicationList[i]; 
        delete publicationList[i];
        publicationList[i] = nullptr;
    }
    //add the publicaton
    
    largerPList[publicationListSize] = pub;
    publicationListSize ++;
    //replace old list with new one
    publicationList = largerPList;*/


}

//---------------------------------------------------------------------------
// returnPub
// removes a publication from the list. return false if it fails
bool Client::returnPub(PubInfo* pub)
{
    //find matching publication
    for (int i = 0; i < publicationListSize; i++)
    {
        if (publicationList[i] != nullptr)
        {
            if (*publicationList[i] == *pub)
            {
                //remove the element from the list
                delete publicationList[i];
                publicationList[i] = nullptr;
                return true;
            
            }
        }
        
    } // not found
    return false;
}

//---------------------------------------------------------------------------
// addHistory
// adds a command to the history
void Client::addHistory(Command* cmd)
{
    for (int i = 0; i < commandListSize; i++)
    {
        if (commandList[i] == nullptr)
        {
            //add to the earliest nullptr
            commandList[i] = cmd;
            break;
            
        }
    }
}

//---------------------------------------------------------------------------
// getHistory
// gets the histoy of this client
Command** Client::getHistory()
{
    return commandList;
}
//---------------------------------------------------------------------------
// getCommandListSize
// gets the command list size
int Client::getCommandListSize()
{
    return commandListSize;
}
//---------------------------------------------------------------------------
// getFirstName
// gets first name of client
string Client::getFirstName()
{
    return firstName;
}


//---------------------------------------------------------------------------
// getLastName
// gets Last name of client
string Client::getLastName()
{
    return lastName;
}
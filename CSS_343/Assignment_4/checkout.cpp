//checkout.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "checkout.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// sets cID, pub type, copy type, pubInfo
CheckOut::CheckOut(int cID, char pubType, char copyType, PubInfo* pI)
{
    this->cID = cID;
    this->pubType = pubType;
    this->copyType = copyType;
    this->pubInfo = pI;
}

//---------------------------------------------------------------------------
// Destructor
// deletes pubInfo pointer
CheckOut::~CheckOut()
{
    delete pubInfo;
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// Execute()
// checks out a publication for a client
// 
void CheckOut::execute(Library& lib)
{
    //cout << "running check out" << endl;
    //get the target publication and client
    Media* targetPub = lib.retrievePublication(pubType, *pubInfo);
    Client* targetClient = lib.retrieveClient(cID);
    //if client and publication is valid
    if (targetPub!= nullptr && targetClient!= nullptr) 
    {
        //check if there are copies available
        //remove 1 copy from the publication
        if (targetPub->removeCopies())
        {
            //add the publication info to the client's 
            //list of checked out publications

            //make copy of pubInfo
            PubInfo* pICopy = new PubInfo(*pubInfo);
            targetClient->checkOutPub(pICopy);

            //add this command to history
            targetClient->addHistory(const_cast<CheckOut*>(this));
        }   
        else
        {
            //when there were no copies avialable
            cout << "ERROR: there is no copies of this publication avialable"; 
            cout << endl;
            delete this;
        }
           
    } else
    {
        //delete self in the event of failure
        delete this;
    }
    targetPub = nullptr;
    //targetClient = nullptr;
}

//---------------------------------------------------------------------------
// getCommandName
// gets the name of the command (for history to use)
string CheckOut::getCommandName()
{
    return commandName;
}

//---------------------------------------------------------------------------
// getPubInfo
// gets the PubInfo (assumes it's used in a child of command that actually uses
// PubInfo)
PubInfo* CheckOut::getPubInfo()
{
    return pubInfo;
}

//---------------------------------------------------------------------------
// getPubType
// gets the PubType (assumes it's used in a child of command that actually uses
// PubInfo)
char CheckOut::getPubType()
{
    return pubType;
}

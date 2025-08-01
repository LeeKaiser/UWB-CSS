//checkout.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "return.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Return::Return(int cID, char pubType, char copyType, PubInfo* pI)
{
    this->cID = cID;
    this->pubType = pubType;
    this->copyType = copyType;
    this->pubInfo = pI;
}

//---------------------------------------------------------------------------
// Destructor
// 
Return::~Return()
{
    delete pubInfo;
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// Execute()
// checks out a publication for a client
void Return::execute(Library& lib)
{
    //cout << "running return" << endl;
    //get the target publication and client
    Media* targetPub = lib.retrievePublication(pubType, *pubInfo);
    Client* targetClient = lib.retrieveClient(cID);
    //if client and publication is valid
    if (targetPub!= nullptr && targetClient!= nullptr) 
    {
        //attempt to remove the publication from client's list
        PubInfo* pICopy = new PubInfo(*pubInfo);
        if (targetClient->returnPub(pICopy))
        {
            //if return is successful, add copies avialable
            targetPub->addCopies();
            //add this command to history
            targetClient->addHistory(const_cast<Return*>(this));
        }
        //if not successful
        else{
            cout << "ERROR: Client did not previously check out this";
            cout <<  " publication";
            cout  << endl;
            delete this;
        }
        delete pICopy;
        
    }else //target pub or target client is empty, meaning the input was invalid
    {
        //delete self in event of failure
        delete this;
    }
    targetPub = nullptr;
    //targetClient = nullptr;
}

//---------------------------------------------------------------------------
// getCommandName
// gets the name of the command (for history to use)
string Return::getCommandName()
{
    return commandName;
}

//---------------------------------------------------------------------------
// getPubInfo
// gets the PubInfo (assumes it's used in a child of command that actually uses
// PubInfo)
PubInfo* Return::getPubInfo()
{
    return pubInfo;
}

//---------------------------------------------------------------------------
// getPubType
// gets the PubType (assumes it's used in a child of command that actually uses
// PubInfo)
char Return::getPubType()
{
    return pubType;
}
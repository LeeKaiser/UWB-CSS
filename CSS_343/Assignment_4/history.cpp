//display.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "history.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// sets cID
History::History(int cID)
{
    this->cID = cID;
}

//---------------------------------------------------------------------------
// Destructor
// 
History::~History()
{
   
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// Execute()
// checks out a publication for a client
void History::execute(Library& lib)
{
    //cout << "running history" << endl;
    //print client's history
    Client* targetClient = lib.retrieveClient(cID);
    //get a reference to the client's history
    if (targetClient != nullptr)
    {
        int histSize = targetClient->getCommandListSize();
        Command** clientHist = targetClient->getHistory();
        //print user info
        cout << left << setw(CLIENT_ID_MAX_LENGTH) << cID;
        cout << targetClient->getFirstName() << "," ;
        cout << targetClient->getLastName() << ":" << endl;
        //print all the commands
        for (int i = 0; i < histSize; i++)
        {
            //when there is a command in history
            if (clientHist[i] != nullptr)
            {
                //print command type
                cout << "   ";
                cout << left << setw(COMMAND_NAME_MAX_LENGTH) ;
                cout << clientHist[i]->getCommandName();
                //get the publication referenced in the history then print it
                Media* targetPub = lib.retrievePublication(
                    clientHist[i]->getPubType(), *clientHist[i]->getPubInfo());
                targetPub->printInfo();
            }
            //when there isn't a command in history
            else
            {
                break;
            }
            
            
        }
        cout << endl;
    }
    

    //delete self after execution
    delete this;
}
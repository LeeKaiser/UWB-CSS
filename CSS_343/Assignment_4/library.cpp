//library.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "library.h"
#include "fiction.h"
#include "childrens.h"
#include "periodical.h"
#include "client.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Library::Library()
{
    //instantiate the client hashtable
    for (int i = 0; i < EXPECTED_CLIENTS ; i++)
    {
        for (int j = 0; j < EXPECTED_CLIENTS ; j++)
        {
            clientHashTable[i][j] = nullptr;
        }
    }
}

//---------------------------------------------------------------------------
// Destructor
// 
Library::~Library()
{
    //delete every element in the client hash table
    for (int i = 0; i < EXPECTED_CLIENTS ; i++)
    {
        for (int j = 0; j < EXPECTED_CLIENTS ; j++)
        {
            if (clientHashTable[i][j] != nullptr)
            {
                delete clientHashTable[i][j];
            }
            else{
                break;
            }
        }
    }
}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// buildPublicationContainers
// 
void Library::buildPublicationContainers(ifstream& infile)
{
    //go through the file
    for (;;)
    {
        //stop at end of file
        if (infile.eof())
        {
            break;
        }
        //make new media
        Media* newPub = fact.buildMedia(infile);
        if (newPub != nullptr) //if publication successfully generated
        {
            mediaContainer[newPub->getPubType()].insert(newPub);
        }
        
    }
}

//---------------------------------------------------------------------------
// retrieveContainer
// returns one of the collection of medias
Container& Library::retrieveContainer(char code)
{
    /*if (!validatePubType(code))
    {
        cout << "ERROR: Invalid publication Type" << endl;
    } //i'm not sure how I should terminate if input was not valid*/
    return mediaContainer[code];
}

//---------------------------------------------------------------------------
// buildClientsHashTable
// builds the hashtable that holds clients. (open hashing)
void Library::buildClientsHashTable(ifstream& infile)
{
    //loop through the file
    for (;;)
    {
        //stop at end of file
        if (infile.eof())
        {
            break;
        }
        
        //make new client
        Client* newClient = fact.buildClient(infile);
        if (newClient != nullptr) //if client is successfully generated
        {
            //hash function f(x) = x % 100 (X is ID)
            int hashIndex = newClient->getClientID() % 100;
            //add client to hash function
            for (int i = 0; i < EXPECTED_CLIENTS; i++)
            {
                //if an empty spot is found
                if (clientHashTable[hashIndex][i] == nullptr)
                {
                    //make & add client)
                
                    clientHashTable[hashIndex][i] = newClient;
                    break;
                }
            }
        }
        
    }
}

//---------------------------------------------------------------------------
// runAllCommands
// builds and runs all commands in infile
void Library::runAllCommands(ifstream& infile) const
{
    for (;;)
    {
        //stop at end of file
        if (infile.eof())
        {
            break;
        }
        //build the command
        Command* comm = fact.buildCommand(infile);
        if (comm != nullptr)
        {
            //execute command if successful
            comm->execute(const_cast<Library&>(*this));
        }
    }
}

//---------------------------------------------------------------------------
// retrievePublication
// retrieves a publication for the command to use
Media* Library::retrievePublication(char pubType, const PubInfo& pI)
{
    
    Media* ret;
    //validate publication type
    if (!validatePubType(pubType))
    {
        cout << "ERROR: Invalid publication Type" << endl;
        return nullptr;
    }
    // get the publication
    bool success = mediaContainer[pubType].retrieve(pI, ret);
    if (success)
    { 
        return ret;
    }
    // if publication is not present
    cout << "ERROR: Failed to find Publication" << endl;
    return nullptr;
}

//---------------------------------------------------------------------------
// retrieveClient
// retrieves a client for the command to use
Client* Library::retrieveClient(int cID) const
{
    //hash function f(x) = x % 100 (X is ID)
    int hashIndex = cID % 100;
    for (int i = 0; i < EXPECTED_CLIENTS; i++)
    {
        if (clientHashTable[hashIndex][i] == nullptr)
        {
            //if list ends, break
            break;
        } 
        else if (clientHashTable[hashIndex][i]->getClientID() == cID)
        {
            
            //if found, return
            return clientHashTable[hashIndex][i];
        }
    }
    //if not found
    cout << "ERROR: Failed to find Client" << endl;
    return nullptr;
}

//---------------------------------------------------------------------------
// validatePubType
// return ture if the pubtype is valid, false otherwise
bool Library::validatePubType(char pubType)
{
    //check if pubtype matches the ones library accepts
    for (int i = 0; i < NUMBER_OF_PUB_TYPES ; i++)
    {
        if (categories[i] == pubType)
        {
            return true;
        }
    }
    return false;
}
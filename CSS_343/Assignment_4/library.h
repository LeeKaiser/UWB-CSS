//---------------------------------------------------------------------------
// library.h - Kaiser Lee
//---------------------------------------------------------------------------
// Library that holds several publications of varying types.
// stores all the registered clients in a hash table
// hash function for clients:  f(x) = x % 100 (X is ID)
// currently set to accept publication types Fiction, Childrens, and Periodical
// Assumptions:
// map of media containers hold all accepted types
// categories list has all accepted media categories
//---------------------------------------------------------------------------
#ifndef LIBRARY_H
#define LIBRARY_H

using namespace std;
#include <iostream>
#include <fstream>
#include <map>
#include "container.h"
#include "factory.h"
class Client;
class Media;
class Publication;
class Fiction;
class Childrens;
class Periodical;
class PubInfo;

class Library {
public:
    Library(); //constructor
    ~Library(); //destructor
    void getHistory(Client); //view history of clients
    void buildPublicationContainers(ifstream&) ; 
    //builds hash table of publication categories
    void buildClientsHashTable(ifstream&); //builds hash table of clients
    void runAllCommands(ifstream&) const; //builds hash table of clients
    Media* retrievePublication(const char pubType, const PubInfo&); 
    //retrieves a publication for the command
    Client* retrieveClient(int cID) const;
    //retrieves a client for the command
    Container& retrieveContainer(char code);

private:
    // a map of media containers 
    map<char,Container> mediaContainer =
    {
        {'F', Container()}, //contains fiction
        {'C', Container()}, //contains childrens
        {'P', Container()}  //contains periodical
    };
    static const int NUMBER_OF_PUB_TYPES = 3;
    char categories[NUMBER_OF_PUB_TYPES] = { 'F','P','C'}; 
    //valid keys for publication types
    //holds different categories of list of publication.
    Factory fact = Factory();

    // a hash table of clients 
    static const int EXPECTED_CLIENTS = 100; 
    int currentClientsSize = EXPECTED_CLIENTS;
    Client* clientHashTable[EXPECTED_CLIENTS][EXPECTED_CLIENTS];

    //private methods
    void increaseClientHTSize(); //increase clients hash table size if there 
    // are more clients than expected
    void insertClient(); // insert a client into hash table
    bool retrievePubHelper(char pubType, const PubInfo& pI, Media* ret);
    bool validatePubType(char pubType); 
    //return true if valid pub type to avoid error
};

#endif
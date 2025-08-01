//---------------------------------------------------------------------------
// main.cpp - Kaiser Lee
//---------------------------------------------------------------------------
// Main method that tests the Assignment 4 program. 
// uses Data4Pubs.txt, Data4Clients.txt, and Data4Commands.txt
// Assumptions:
// Data4Pubs.txt, Data4Clients.txt, and Data4Commands.txt are present
// 
//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include "library.h"

int main()
{
    // begin by testing building publication collection and displaying it
    //cout << "Testing build publications" << endl; // debug
    Library lib = Library();
    ifstream infilePubs("Data4Pubs.txt");
    if (!infilePubs) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    lib.buildPublicationContainers(infilePubs);
    // build the clients
    //cout << "Testing build Clients" << endl; // debug
    ifstream infileClient("Data4Clients.txt");
    if (!infileClient) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    lib.buildClientsHashTable(infileClient);
    // run the commands in the commands file
    //cout << "Testing run commands" << endl; // debug
    ifstream infileCommands("Data4Commands.txt");
    if (!infileCommands) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    lib.runAllCommands(infileCommands);
}
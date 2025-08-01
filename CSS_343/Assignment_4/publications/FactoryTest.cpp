// testing file for factory (not part of lab, just for testing)
#include <fstream>
#include <iostream>
using namespace std;
#include "factory.h"

int main()
{
    ifstream infile("FactoryTestData.txt");
    if (!infile) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    char code;
    for (;;)
    {
        if (infile.eof())
        {
            break;
        }
        infile >> code;
        Factory fact = Factory();
        Media* x = fact.buildMedia(code, infile);
        x->printInfo();
        delete x;
    }
    

}
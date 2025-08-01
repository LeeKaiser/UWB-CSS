//display.cpp file
//for assignment 4 CSS 343
//Kaiser Lee

#include "display.h"

//---------------------------------------------------------------------------
// Constructors & destructors
//---------------------------------------------------------------------------
// Default Constructor
// 
Display::Display()
{
}

//---------------------------------------------------------------------------
// Destructor
// 
Display::~Display()
{
   
}

//---------------------------------------------------------------------------
// Methods
//---------------------------------------------------------------------------
// Execute()
// checks out a publication for a client
// deletes itself after finishing command
void Display::execute(Library& lib)
{
    //cout << "running display" << endl;
    //print library information
    cout << "FICTION PUBLICATIONS" << endl;
    cout << left << setw(AVAIL_MAX_LENGTH) << "AVAIL";
	cout << left << setw(AUTHOR_MAX_LENGTH) << "AUTHOR";
	cout << left << setw(TITLE_MAX_LENGTH) << "TITLE";
	cout << right << setw(YEAR_MAX_LENGTH) << "YEAR";
	cout << endl;
    cout << lib.retrieveContainer('F');

    cout << "CHILDRENS PUBLICATIONS" << endl;
    cout << left << setw(AVAIL_MAX_LENGTH) << "AVAIL";
	cout << left << setw(TITLE_MAX_LENGTH) << "TITLE";
	cout << left << setw(AUTHOR_MAX_LENGTH) << "AUTHOR";
	cout << right << setw(YEAR_MAX_LENGTH) << "YEAR";
    cout << endl;
    cout << lib.retrieveContainer('C'); 

    cout << "PERIODICAL PUBLICATIONS" << endl;
    cout << left << setw(AVAIL_MAX_LENGTH) << "AVAIL";
    cout << left << setw(YEAR_MAX_LENGTH) << "YEAR";
	cout << left << setw(MONTH_MAX_LENGTH) << "MONTH";
	cout << left << setw(TITLE_MAX_LENGTH) << "TITLE";
	cout << endl;
    cout << lib.retrieveContainer('P');
    delete this;
}
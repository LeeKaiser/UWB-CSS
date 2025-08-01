//file graphm.cpp
//for assignment 3 CSS 343
//Kaiser Lee

#include "graphm.h"

//---------------------------------------------------------------------------
// Constructors & Destructors
//---------------------------------------------------------------------------
// Default Constructor
GraphM::GraphM(){}
//---------------------------------------------------------------------------
// Destructor
GraphM::~GraphM(){}

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
// buildGraph
// accept a file and read file to build the matrix.
// assumptions:
// file is formatted correctly. first value should be 
// an int representing amount of nodes, then there should be list of 
// data for each node
// then there should be all the edges in the graph.
void GraphM::buildGraph(istream& infile)
{
    int fromNode, toNode;   // from, to node ends

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data
    
   
    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                   // used to read to end of line holding size
    getline(infile, s);         // essentially throw away chars after size
    // read graph node information
    for (int i=1; i <= size; i++) {
        // read using setData of the NodeData class,
        // where graphNodeArray is the array of GraphNodes and data is 
        // the NodeData object of GraphNode
        data[i].setData(infile);
        
    }
    
    initializeMatrix();
    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode == 0) return;              // end of edge data
        // if valid, put into the adjacency edge STL list for fromNode
        try 
        {
            matrix[fromNode][toNode] = 1;
        }
        catch (exception E){}
    }

}

//---------------------------------------------------------------------------
// initializeMatrix
// initializes matrix to all be 0 to avoid errors relating to uninitialized
// values
void GraphM::initializeMatrix()
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            // initialize all values to 0
            matrix[i][j] = 0;
        }
    }
}

//---------------------------------------------------------------------------
// displayGraph
// displays all the nodes and all the edges that each node has.
void GraphM::displayGraph()
{
    cout << "Graph:" << endl;
    //print out every node
    for (int n = 1; n <= size; n++)
    {
        cout << "Node " << n << "          " << data[n] << endl;
        //print all edge in node n
        for (int e = 1; e <= size;e++ )
        {
            //debug
            //cout << n << "," << e << "  " << matrix[n][e]<< endl;
            if (matrix[n][e] == 1)
            {
                cout << "   " << "edge  " << n << "  " << e << endl; 
            }
        }
    }
}

//---------------------------------------------------------------------------
// depthFirstSearch
// use depth first search algorithm to generate a list of all the nodes. 
void GraphM::depthFirstSearch()
{
    //initialize all visited as false so it can be used multiple times 
    //without problems
    for (int i = 1; i <= size; i++)
    {
        visited[i] = false;
    }
    // start dfs for every unvisited nodes
    cout << "Depth-first ordering:    ";
    for (int v = 1; v <= size; v++)
    {
        //only star dfshelper if v is not visited
        if (!visited[v])
        {
            dFSHelper(v);
        }
    }
    cout << endl;
}

//---------------------------------------------------------------------------
// dFSHelper
// recursive function that sets v as visited then recurses with all the nodes
// that had a path from v
void GraphM::dFSHelper(int v)
{
    // print v then find w that goes from v 
    cout << v << " " ;
    //set w as visited
    visited[v] = true;
    // find valid w then use dfs helper on it.
    for (int w = 1; w <= size; w++)
    {
        //debug
        //    cout << v << "," << w << endl;
        //if path to w is found that is not visited
        if (!visited[w] && matrix[v][w] == 1)
        {
            dFSHelper(w);
        }
    }
}
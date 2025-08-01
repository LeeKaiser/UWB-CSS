//file graphm.h
//for assignment 3 CSS 343
//Kaiser Lee

#include <iostream>
using namespace std;
#include "nodedata.h"

//---------------------------------------------------------------------------
// GraphM
//
// represent a graph through adjacency matrix. 
// data holds data of each node
// matrix holds info on if there are path from one node to another
//
// Assumption: 
// depthFirstSearch & displayGraph is used after using buildGraph
//---------------------------------------------------------------------------

class GraphM {
public:
    GraphM();   // constructor
    ~GraphM();  // destructor
    void buildGraph(istream& infile); // builds graph based on input
    void displayGraph(); // display the whole graph
    void depthFirstSearch();

private:
    static const int MAXNODES = 100;
    NodeData data[MAXNODES];// graph node data information, at most 100 nodes
    bool visited[MAXNODES]; // for depth-first, whether visited
    int matrix[MAXNODES][MAXNODES]; // adjacency matrix for edges
    //first index is from, second index is to
    int size; // number of nodes in the graph

    void dFSHelper(int v); //helper for DFS
    void initializeMatrix(); // initializes matrix to avoid erorrs.
};
//file graphl.h
//for assignment 3 CSS 343
//Kaiser Lee

#include <iostream>
using namespace std;
#include "nodedata.h"

//---------------------------------------------------------------------------
// GraphL 
//
// represent a graph through adjacency list. 
// graphNodeArray is the list that holds GraphNode, which holds data and list
// of edges it has to connect with other nodes. 
//
// Assumption: 
// display and displayAll is used after using findShortestPath
// findShortestPath is used after using buildGraph
//---------------------------------------------------------------------------

struct Edge { // structs for simplicity (has no functions)
int toNode, cost; // adjacent node of edge, value of the edge
};
struct GraphNode { // structs for simplicity (has no functions)
Edge edgeList[100]; // list of edges (edge nodes), the adjacent graph nodes
NodeData data; // information on the graph node
};

class GraphL {
public:
    GraphL(); // constructor
    ~GraphL(); // destructor

    void buildGraph(istream& infile); // builds graph based on input
    void findShortestPath();  // performs algorithm
    void displayAll() const; // Demonstrate algorithm works correctly
    // Display shortest path with path and node descriptions
    void display(int source, int dest) const; 
    

private:
    struct TableType {
        bool visited = false; // whether node has been visited
        int dist = -1; // currently known shortest distance from source
        //uninitialized distance is represented as -1
        int path = 0; // previous node in path having min distance
    };
    
    static const int MAXNODES = 100;
    GraphNode graphNodeArray[MAXNODES];
    int size; // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores Dijkstra information
    // array (or vector) of GraphNode, which is the adjacency list
    // static array is fine, assume at most 100 nodes
    int nodeEdgeIndex[MAXNODES];     
    // used to keep track of index for each edgelist
    int findV(int source); // finds smallest element not visited in T
    void findPaths(int source, int v); // finds all path from v
    //returns all nodes that needs to be went to in order to reach dest 
    //from source.
    void pathInstructions(int source, int dest) const; 
};
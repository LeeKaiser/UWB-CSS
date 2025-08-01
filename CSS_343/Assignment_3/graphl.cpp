//file graphl.cpp
//for assignment 3 CSS 343
//Kaiser Lee

#include "graphl.h"

//---------------------------------------------------------------------------
// Constructors & Destructors
//---------------------------------------------------------------------------
// Default Constructor
GraphL::GraphL(){}
//---------------------------------------------------------------------------
// Destructor
GraphL::~GraphL(){}

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
void GraphL::buildGraph(istream& infile)
{
    int fromNode, toNode, value;   // from, to node ends and value of edge

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data
   
    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                   // used to read to end of line holding size
    getline(infile, s);         // essentially throw away chars after size
    // read graph node information
    for (int i=1; i <= size; i++) {
        // read using setData of the NodeData class, where graphNodeArray is 
        // the array of GraphNodes and data is the 
        // NodeData object of GraphNode
        graphNodeArray[i].data.setData(infile);
        nodeEdgeIndex[i] = 0;
    }
    
    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode >> value;
        if (fromNode == 0) return;              // end of edge data
        // if valid, put into the adjacency edge STL list for fromNode
        try 
        {
            graphNodeArray[fromNode].edgeList[nodeEdgeIndex[fromNode]]
            .toNode = toNode;
            graphNodeArray[fromNode].edgeList[nodeEdgeIndex[fromNode]]
            .cost = value;
            nodeEdgeIndex[fromNode]++;
        }
        catch (exception E){}
    }

}

//---------------------------------------------------------------------------
// findShortestPath
// use dijkstra's path to find shortest path from one to another
void GraphL::findShortestPath()
{
    // loop to do algorithmn for each starting point
    for (int source = 1; source <= size; source++)
    {
        //cout << "source: " << source << endl;
        T[source][source].dist = 0;
        
        
        // loop for each possible v
        for (int i = 1; i <= size; i++)
        {
            
            int v = findV(source);
            // find V and mark it as visited
            T[source][v].visited = true; // sets V as visited
            //cout << "v = " << v << endl;
            // set dist and path for all edge from source
            //checks each node to see if it connects from v
            if (v != 0)
            {
                findPaths(source,v);
            }
            
        }
    }
}
//---------------------------------------------------------------------------
// findPaths
// find all the paths from v to all possible w 
// assumption: only uses the first path found from v to w
void GraphL::findPaths(int source, int v)
{
    // for every possible w
    for (int w = 1; w <= size; w++)
    {
        //W that is not visited 
        if (T[source][w].visited == false)
        {
            // find the path to w from v if it exists
            for (int ELIndex = 0; ELIndex < nodeEdgeIndex[v]; ELIndex++)
            {
                // if it's correct path
                if (graphNodeArray[v].edgeList[ELIndex].toNode == w)
                {
                    //calculate distance
                    int distance = T[source][v].dist + 
                        graphNodeArray[v].edgeList[ELIndex].cost;
                    //add dist if it is less than current dist or there
                    // is no dist for it yet
                    if (T[source][w].dist == -1 || 
                        T[source][w].dist > distance)
                    {
                        //add dist
                        T[source][w].dist = distance;
                        //add path
                        T[source][w].path = v;   
                        //finish loop
                        ELIndex = 100;                         
                    }
                }
            }
        }
        
    }
}

//---------------------------------------------------------------------------
// findv
// finds which value should v be by finding the lowest distance.
int GraphL::findV(int source)
{
    
    int v = 0;
    int shortest = -1;
    for (int i = 1; i <= size; i++)
    {
        // if distance is not infinite and is shortest or 
        // shortest not found yet and has not been visited yet
        if (T[source][i].dist != -1 && 
            (T[source][i].dist < shortest || shortest == -1)
            && T[source][i].visited == false)
        {
            v = i;
            shortest = T[source][i].dist;
        }
    }
    return v;
}

//---------------------------------------------------------------------------
// displayAll
// assumes findShortestPath has been run first, meaning T is correct
void GraphL::displayAll() const
{
    cout << "Description    From node   To node     Dijkstra's Path" << endl;
    // go through all possible source
    for (int source = 1; source <= size; source++)
    {
        
        cout << graphNodeArray[source].data << endl;
        // go throguh all possible destinations
        for (int dest = 1; dest <= size; dest++)
        {
            
            // does not show source to source
            if (dest != source)
            {
                cout << "                   ";
                // print source and destination
                cout << source << "         ";
                cout << dest << "           ";
                //print out path
                if (T[source][dest].dist == -1)
                {
                    cout << "---" << endl;
                }
                else
                {
                    //print distance from source to destination
                    cout << T[source][dest].dist << "       ";
                    //write the path from source to destination
                    pathInstructions(source,dest);
                    cout << endl;
                }
            }
        }
    }
    
}

//---------------------------------------------------------------------------
// display
// display information about going from one path to another
void GraphL::display(int source, int dest) const
{
    // print the info for the path
    cout << "   " << source << "    " << dest << "    ";
    // if it is not possible to reach dest from source, write ---
    if (T[source][dest].dist == -1)
    {
    cout << "---" << endl;
    }
    else
    {
        // write basic info of the path
        cout << T[source][dest].dist << "    ";
        pathInstructions(source,dest);
        cout << endl;
        //print the names of path
        int instruction[size];
        int previous = dest;
        //fill instruction with path from source to dest
        for (int i = 1; i <= size; i++)
        {
            instruction[size-i] = 0;
            if (T[source][previous].path != 0)
            {
                instruction[size-i] = previous;
                previous = T[source][previous].path;
            }
        }
        //print instructions
        cout << graphNodeArray[source].data << endl ;
        for (int i = 0; i < size; i++)
        {
        
            if (instruction[i] != 0)
            {
                cout << graphNodeArray[instruction[i]].data << endl ;
            }
        }
    }
}
//---------------------------------------------------------------------------
// pathInstructions
// outputs the path that needs to be taken to go from source to dest[ination]
// assumes instruction array is size of length
void GraphL::pathInstructions(int source, int dest) const
{
    int instruction[size];
    int previous = dest;
    //fill instruction with path from source to dest
    for (int i = 1; i <= size; i++)
    {
        instruction[size-i] = 0;
        if (T[source][previous].path != 0)
        {
            instruction[size-i] = previous;
            previous = T[source][previous].path;
        }
    }
    //print instructions
    cout << source << " " ;
    for (int i = 0; i < size; i++)
    {
        
        if (instruction[i] != 0)
        {
            cout << instruction[i] << " " ;
        }
    }
}
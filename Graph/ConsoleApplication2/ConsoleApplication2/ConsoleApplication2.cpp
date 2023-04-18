
#include <iostream>
#include "Graph.h"

int main()
{
    Graph g;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(1, 4, 5);
    g.addEdge(4, 3, 1);
    g.addEdge(5, 3, 1);
    g.addEdge(4, 7, 6);
    g.addEdge(3, 6, 1);
    g.addEdge(3, 7, 1);
    g.addEdge(3, 8, 8);
    g.addEdge(5, 8, 1);
    g.addEdge(8, 6, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(9, 6, 1);
    g.addEdge(9, 5, 1);

    g.show();
    g.width(0);
    g.depth(0);
    std::cout<<g.pathCount(0, 9);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

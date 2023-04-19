
#include <iostream>
#include "Graph.h"
#include "Tree.h"
int main()
{
    //Graph g;

    //g.addVertex(0);
    //g.addVertex(1);
    //g.addVertex(2);
    //g.addVertex(3);
    //g.addVertex(4);
    //g.addVertex(5);
    //g.addVertex(6);
    //g.addVertex(7);
    //g.addVertex(8);
    //g.addVertex(9);

    //g.addEdge(0, 1, 1);
    //g.addEdge(0, 2, 1);
    //g.addEdge(0, 3, 1);
    //g.addEdge(2, 5, 1);
    //g.addEdge(1, 4, 5);
    //g.addEdge(4, 3, 1);
    //g.addEdge(5, 3, 1);
    //g.addEdge(4, 7, 6);
    //g.addEdge(3, 6, 1);
    //g.addEdge(3, 7, 1);
    //g.addEdge(3, 8, 8);
    //g.addEdge(5, 8, 1);
    //g.addEdge(8, 6, 1);
    //g.addEdge(7, 6, 1);
    //g.addEdge(9, 6, 1);
    //g.addEdge(9, 5, 1);

    //g.show();
    //g.width(0);
    //g.depth(0);
    //std::cout<<g.pathCount(0, 9);
    //g.findMinDistanceDecstr(0);
    //g.findMinDistancesFloyd();

    Tree tree;

    tree.setRoot(2); // задали корень
    tree.addNode(2, 4); // добавляем узлы
    tree.addNode(2, 0);
    tree.addNode(2, 3);
    tree.addNode(4, 1);
    tree.addNode(1, 5);
    tree.addNode(1, 6);

    //tree.delNode(4); // удалили узел 4
}


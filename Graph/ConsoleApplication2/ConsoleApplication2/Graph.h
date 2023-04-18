#pragma once
#ifndef __GRAPH__
#define __GRAPH__

#define SIZE 10

class Graph {
public:
    void depth(int start);
    Graph();
    // добавление вершины
    void addVertex(int vnumber);
    // добавление ребра
    void addEdge(int v1, int v2, int weight);
    // удаление вершины
    void delVertex(int vnumber);
    // удаление ребра
    void delEdge(int v1, int v2);
    void show();
    //поиск количества путей

    void pathCountInner(int current, int to, bool visited[], int& count);
    int pathCount(int from, int to);
    void width(int start);
    void depthInner(int current, bool visited[]);

private:
    bool edgeExists(int v1, int v2);
    bool vertexExists(int v);

    int matrix[SIZE][SIZE]; // матрица смежности

    int vertexes[SIZE]; // хранилище вершин
    int vertexCount; // количество добавленных вершин
};
#endif 
//rg
#pragma once
#ifndef __GRAPH__
#define __GRAPH__

#define SIZE 10

class Graph {
public:
    void depth(int start);
    Graph();
    // ���������� �������
    void addVertex(int vnumber);
    // ���������� �����
    void addEdge(int v1, int v2, int weight);
    // �������� �������
    void delVertex(int vnumber);
    // �������� �����
    void delEdge(int v1, int v2);
    void show();
    //����� ���������� �����

    void pathCountInner(int current, int to, bool visited[], int& count);
    int pathCount(int from, int to);
    void width(int start);
    void depthInner(int current, bool visited[]);

private:
    bool edgeExists(int v1, int v2);
    bool vertexExists(int v);

    int matrix[SIZE][SIZE]; // ������� ���������

    int vertexes[SIZE]; // ��������� ������
    int vertexCount; // ���������� ����������� ������
};
#endif 
//rg
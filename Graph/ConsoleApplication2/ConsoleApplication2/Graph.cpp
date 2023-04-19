#include "Graph.h"
#include <iostream>

#define VERYBIGINT 1000000000 // ����� ������� �����

#define VERYBIGINT 1000000000

void Graph::findMinDistancesFloyd() //�����
{
    int weights[SIZE][SIZE]; // ������� �����
    // ������������ �������
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // ���� �� ����� ���� ����� 0
            }
            else {
                if (!edgeExists(i, j))
                {
                    weights[i][j] = VERYBIGINT; // ���� ����� ���
                }
                else {
                    weights[i][j] = matrix[i][j]; // ���� ����� ����
                }
            }
        }
    }



    for (int k = 0; k < vertexCount; k++) // �������� �� k
    {
        int ck = vertexes[k]; // ������� ����� �������
        for (int i = 0; i < vertexCount; i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i];
            for (int j = 0; j < vertexCount; j++)
            {
                if (j == k)
                    continue;
                int cj = vertexes[j];
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // �������� �������� �����
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    for (int i = 0; i < vertexCount; i++)
    {
        // ����� ���� ����������� ����� �� ������� '0'
        std::cout << "V" << i << ": " << weights[0][vertexes[i]] << ", ";
    }
}

int Graph::findMinWayDFS(int from, int to) {

    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;
    int min = VERYBIGINT; // ��������� ����������� ����������
    int currentDistance = 0;

    inner(from, to, visited, min, currentDistance);
    return min;
}

void Graph::inner(
    int current, int to, bool visited[], int& min, int currentDistance)
{
    if (current == to)
    {
        // ���� ������ � ������� �������, ���������� ������� ���� � �����������
        if (min > currentDistance)
        {
            // ���� ����� ���������� ������, ����������
            min = currentDistance;
        }
        return;
    }
    visited[current] = true; // ��������� ������� ����������
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
        {
            // ��������� �������� ��� ���� ������������ ������� ������
            int newDist = currentDistance + matrix[current][i];
            inner(i, to, visited, min, newDist);
        }
    }
    // ��������, ��� ���� ��� �� �������� ��� �������
    visited[current] = false;
}

void Graph::findMinDistanceDecstr(int fromVert) //��������
{
    int distances[SIZE]; // ������ �����
    for (int i = 0; i < SIZE; i++) // ������������� �����
    {
        distances[i] = VERYBIGINT;
    }
    distances[fromVert] = 0;

    bool passed[SIZE]; // �������, ��� ������� ��������
    for (int i = 0; i < SIZE; i++)
    {
        passed[i] = false; // ��� ���������� ����������
    }
    // ��������� ��������� ������� �� �������
    int currentVertexNum = fromVert;
    int min_dist = 0;
    while (min_dist != VERYBIGINT)
    {
        passed[currentVertexNum] = true; // ���������� �������

        for (int i = 0; i < SIZE; i++)
        {
            // ��� ������� ����� ������������� �����
            if (edgeExists(currentVertexNum, i)
                && distances[currentVertexNum] + matrix[currentVertexNum][i] < distances[i])
                distances[i] =
                distances[currentVertexNum] + matrix[currentVertexNum][i];
        }
        min_dist = VERYBIGINT;
        for (int i = 0; i < SIZE; i++)
        {
            // �������� ����� ������� �������
            if (vertexExists(i) && !passed[i] && distances[i] < min_dist) // ����� ����� �������
            {
                min_dist = distances[i];
                currentVertexNum = i;
            }
        }
    }

    for (int i = 0; i < vertexCount; i++) // ����� ����������
    {
        std::cout << "V" << i << ": " << distances[vertexes[i]] << ", ";
    }
    std::cout << std::endl;
}

void Graph::pathCountInner(int current, int to, bool visited[], int& count)
{
    if (current == to)
    {
        // ���� ����� �� ������ �������, ����������� ������� �����
        // � �������
        count++;
        return;
    }
    visited[current] = true; // �������� ��� ����������
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
        {
            pathCountInner(i, to, visited, count);
        }
    }
    // ��������, ��� ���� ��� �� �������� ��� �������
    visited[current] = false;
}

int Graph::pathCount(int from, int to)
{
    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;
    int count = 0; // ���������
    pathCountInner(from, to, visited, count);
    return count;
}

void Graph::width(int start)
{
    int queue_to_visit[SIZE]; // ������� ������ ��� ������
    int queueCount = 0;

    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;

    queue_to_visit[queueCount++] = start; // ������ � ������� ��������� �������
    while (queueCount > 0)
    {
        // ������ �� ������� �������
        int current = queue_to_visit[0];
        queueCount--;
        for (int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i + 1];
        }
        visited[current] = true;
        std::cout << "v" << current << " -> ";
        // ����� ������� ������ � ���������� �� � �������
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            for (int j = 0; j < queueCount; j++)
                if (queue_to_visit[j] == i)
                {
                    alreadyAdded = true;
                    break;
                }
            if (!alreadyAdded && edgeExists(current, i) && !visited[i])
                queue_to_visit[queueCount++] = i;
        }
    }
    std::cout << std::endl;
}

void Graph::depthInner(int current, bool visited[])
{
    std::cout << "v" << current << " -> "; // ����� �������
    visited[current] = true; // �������� ��� ����������
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
            depthInner(i, visited); // ���� ���������� ����� � ������� �� ����������, �� ������� �� ���� � ������� �������

    }
}

/* ��� ��������, ���������� �� �����, ����� ���������� �������� �������� ������� ��������� � ��������� ������� ������ (���� ���� �����, �� ������� �� 0).*/

void Graph::depth(int start)
{
    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // �������������� ��� ������������
    depthInner(start, visited); // ������ ��������� 

    std::cout << std::endl;
}

Graph::Graph() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;
    vertexCount = 0;
}
// ���������� �������
void Graph::addVertex(int vnumber)
{
    vertexes[vertexCount] = vnumber;
    vertexCount++;
}
// ���������� �����
void Graph::addEdge(int v1, int v2, int weight)
{
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;
}
// �������� ������������� �����
bool Graph::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] > 0;
}
// �������� ������������� �������
bool Graph::vertexExists(int v)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == v)
            return true;
    return false;
}

void Graph::delVertex(int vnumber)
{
    // �������� ������� � ������ �������
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i][vnumber] = 0;
        matrix[vnumber][i] = 0;
    }
    // ������� ������� �� ������ ������
    int foundIndex = -1;
    for (int i = 0; i < vertexCount; i++)
    {
        if (vertexes[i] == vnumber)
            foundIndex = i;
    }
    vertexCount--;
    for (int i = foundIndex; i < vertexCount; i++)
    {
        vertexes[i] = vertexes[i + 1];
    }
}

void Graph::delEdge(int v1, int v2)
{
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
}

void Graph::show() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

}

#include "Tree.h"
#pragma once
void Node::addChild(Node* newChild)
{
    children[childCount++] = newChild;
}

void Tree::setRoot(int number)
{
    if (root != nullptr)
    {
        // ������� ������, ���� �� ���
        delete root;
        root = nullptr;
    }
    root = new Node(number); // ������������� ����� ������
}

void Tree::addNode(int parentNumber, int newNodeNumber)
{
    Node* parentNode = getNodeByNumber(parentNumber, root); // ����� ��������
    Node* newNode = new Node(newNodeNumber, parentNode); // ������� �����
    parentNode->addChild(newNode); // �������� � ��������
}

Node* Tree::getNodeByNumber(int number, Node* current)
{
    if (current->number == number)
        return current; // ���� ����� ������� � ������ �����, ����������
    for (int i = 0; i < current->childCount; i++)
    {
        // ������� � �������, ���� �� ������ �������
        Node* found = getNodeByNumber(number, current->children[i]);
        if (found)
            return found;
    }
    return nullptr;
}


//// �������� ����
//void Tree::delNode(int number) {
//    // ��� ��� ������ ���� �����
//}
//void Tree::Node::delChild(Node* child) {
//    // ��� ��� ������ ���� �����
//}
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
        // удаляем корень, если он был
        delete root;
        root = nullptr;
    }
    root = new Node(number); // устанавливаем новый корень
}

void Tree::addNode(int parentNumber, int newNodeNumber)
{
    Node* parentNode = getNodeByNumber(parentNumber, root); // нашли родителя
    Node* newNode = new Node(newNodeNumber, parentNode); // создали новую
    parentNode->addChild(newNode); // добавили к родителю
}

Node* Tree::getNodeByNumber(int number, Node* current)
{
    if (current->number == number)
        return current; // если нашли вершину с нужным узлом, возвращаем
    for (int i = 0; i < current->childCount; i++)
    {
        // обходим в глубину, пока не найдем искомую
        Node* found = getNodeByNumber(number, current->children[i]);
        if (found)
            return found;
    }
    return nullptr;
}


//// удаление узла
//void Tree::delNode(int number) {
//    // Ваш код должен быть здесь
//}
//void Tree::Node::delChild(Node* child) {
//    // Ваш код должен быть здесь
//}
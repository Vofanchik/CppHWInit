#pragma once
#define SIZE 10
class Tree { // класс дерево

    struct Node { // структура узла
        Node(int _number, Node* _parent = nullptr) :
            number(_number),
            parent(_parent),
            childCount(0)
        { }
        ~Node()
        {
            for (int i = 0; i < childCount; i++)
            {
                delete children[i];
            }
        }

        int number; // номер вершины

        Node* parent; // родительская вершина
        Node* children[SIZE]; // список дочерних вершин
        int childCount;
        void addChild(Node* newChild);
        // количество детей        
    };

public:
    Tree() {
        root = nullptr;
    }

    void setRoot(int number);
    void addNode(int parentNumber, int newNodeNumber);

    ~Tree() {
        if (root != nullptr)
        {
            delete root; // должны почистить за собой память

        }
    }
private:
    Node* root;

};
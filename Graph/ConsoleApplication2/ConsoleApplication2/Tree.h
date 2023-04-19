#pragma once
#define SIZE 10
class Tree { // ����� ������

    struct Node { // ��������� ����
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

        int number; // ����� �������

        Node* parent; // ������������ �������
        Node* children[SIZE]; // ������ �������� ������
        int childCount;
        void addChild(Node* newChild);
        // ���������� �����        
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
            delete root; // ������ ��������� �� ����� ������

        }
    }
private:
    Node* root;

};
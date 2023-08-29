#include <iostream>
#include <thread>
#include <mutex>

class FineGrainedQueue
{
public:
    struct Node
    {
        int value;
        Node* next;
        std::mutex* node_mutex;
    };

    Node* head;
    std::mutex* queue_mutex;

    FineGrainedQueue()
    {
        head = new Node();
        head->next = nullptr;
        head->value = 0;
        head->node_mutex = new std::mutex();

        queue_mutex = new std::mutex();
    };

    void insert(int value)
    {
        Node* newN = new Node();
        newN->value = value;
        newN->next = nullptr;
        newN->node_mutex = new std::mutex();

        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newN;
    }

    void insertIntoMiddle(int value, int pos)
    {
        int curPos = 1;
        Node* cur, * newN = new Node();
        newN->value = value;
        newN->node_mutex = new std::mutex();
        queue_mutex->lock();
        cur = this->head;
        queue_mutex->unlock();

        if (cur)
            cur->node_mutex->lock();
        while (cur)
        {
            if (curPos == pos)
            {
                newN->node_mutex->lock();
                newN->next = cur->next;
                cur->next = newN;
                newN->node_mutex->unlock();
                cur->node_mutex->unlock();
                return;
            }
            Node* old_cur = cur;
            cur = cur->next;
            if (cur)
                cur->node_mutex->lock();
            else {
                newN->node_mutex->lock();
                newN->next = old_cur->next;
                old_cur->next = newN;
                newN->node_mutex->unlock();
                old_cur->node_mutex->unlock();
                return;
            }
            curPos++;
            old_cur->node_mutex->unlock();
        }
        newN->node_mutex->unlock();

    }

    void show()
    {
        Node* cur = head;
        while (cur->next != nullptr) {
            std::cout << cur->value << " ";
            cur = cur->next;
        }
        std::cout << cur->value << std::endl;
    }
};

int main()
{
    FineGrainedQueue queue;

    for (size_t i = 0; i < 10; i++)
    {
        queue.insert(i);
    }

    std::cout << "Qeue: ";
    queue.show();

    std::cout << "\nThread 1: ";
    std::thread t1(&FineGrainedQueue::insertIntoMiddle, &queue, 100, 3);
    queue.show();
    std::cout << "\nThread 2: ";
    std::thread t2(&FineGrainedQueue::insertIntoMiddle, &queue, 200, 4);
    queue.show();
    std::cout << "\nThread 3: ";
    std::thread t3(&FineGrainedQueue::insertIntoMiddle, &queue, 300, 20);
    queue.show();

        t1.join();
        t2.join();
        t3.join();

    
}

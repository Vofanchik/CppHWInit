#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <future>
#include <chrono>
#include <random>
#include <queue>
#include <vector>


using namespace std;

typedef function<void()> task_type;
typedef future<void> res_type;
template<class T>

class BlockQueue {
public:
    void push(T& item) {
        lock_guard<mutex> l(m_locker);
        m_task_queue.push(item);
        m_notifier.notify_one();
    }
    void pop(T& item) {
        unique_lock<mutex> l(m_locker);
        if (m_task_queue.empty())
            m_notifier.wait(l, [this] {return !m_task_queue.empty(); });
        item = m_task_queue.front();
        m_task_queue.pop();
    }

    bool fast_pop(T& item) {
        lock_guard<mutex> l(m_locker);
        if (m_task_queue.empty())
            return false;
        item = m_task_queue.front();
        m_task_queue.pop();
        return true;
    }
private:
    mutex m_locker;
    queue<T> m_task_queue;
    condition_variable m_notifier;
};

typedef void (*FuncType) (int*, int, int);

class OptimizedThreadPool {
public:
    OptimizedThreadPool() :
        m_thread_count(thread::hardware_concurrency() != 0 ? thread::hardware_concurrency() : 4),
        m_thread_queues(m_thread_count) {}

    void push_task(FuncType f, int* array, int left, int right) {

        int queue_to_push = m_index++ % m_thread_count;
        task_type task = [=] {f(array, left, right);  };
        m_thread_queues[queue_to_push].push(task);
    }

    void threadFunc(int qindex) {
        while (true) {
            task_type task_to_do;
            bool res;
            int i = 0;
            for (; i < m_thread_count; i++) {
                if (res = m_thread_queues[(qindex + i) % m_thread_count].fast_pop(task_to_do))
                    break;
            }

            if (!res) {
                m_thread_queues[qindex].pop(task_to_do);
            }
            else if (!task_to_do) {
                m_thread_queues[(qindex + i) % m_thread_count].push(task_to_do);
            }
            if (!task_to_do) {
                return;
            }
            task_to_do();
        }
    }

    void start() {
        for (int i = 0; i < m_thread_count; i++) {
            m_threads.emplace_back(&OptimizedThreadPool::threadFunc, this, i);
        }
    }

    void stop() {
        for (int i = 0; i < m_thread_count; i++) {

            task_type empty_task;
            m_thread_queues[i].push(empty_task);
        }
        for (auto& t : m_threads) {
            t.join();
        }

    }
private:
    int m_thread_count;
    vector<thread> m_threads;
    vector<BlockQueue<task_type>> m_thread_queues;
    int m_index;
};

class RequestHandler {
public:
    RequestHandler() {
        m_tpool.start();
    }
    ~RequestHandler() {
        m_tpool.stop();
    }
    void pushRequest(FuncType f, int* array, int left, int right) {
        m_tpool.push_task(f, array, left, right);
    }
private:
    OptimizedThreadPool m_tpool;
};

bool make_thread = false;

RequestHandler pool;


void quicksort(int* array, int left, int right) {
    if (left >= right) return;

    int left_bound = left;
    int right_bound = right;

    int middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) {
            left_bound++;
        }
        while (array[right_bound] > middle) {
            right_bound--;
        }

        if (left_bound <= right_bound) {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (make_thread && (right_bound - left > 100000))
    {
        pool.pushRequest(quicksort, array, left, right_bound);
        quicksort(array, left_bound, right);
     
      
    }
    else {
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
    }
}

int main() {

    time_t start, end;
    time(&start);
    unsigned long size = 10000000;
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() / 100;
    }

    cout << "One thread " << endl;
    quicksort(arr, 0, size - 1);

    time(&end);
    double seconds = difftime(end, start);
    printf("%f seconds\n", seconds);

    time(&start);
    make_thread = true;
    for (unsigned int i = 0; i < size; i++) {
        arr[i] = rand() / 100;
    }

    cout << "Pool of thread" << endl;
    quicksort(arr, 0, size - 1);
    
    time(&end);
    seconds = difftime(end, start);
    printf("%f seconds\n", seconds);
    return 0;
}

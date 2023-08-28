#include <iostream>
#include <cstdlib>
#include <future>
#include <mutex>

void fillerFunc(std::vector<int>& mergeVector, long size)
{
    mergeVector.reserve(size);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < size; i++)
    {
        mergeVector.push_back(std::rand() % 100);
    }
}

void merge(std::vector<int>& array, int left, int middle, int right)
{
    int sizeLeft = middle - left + 1;
    int sizeRight = right - middle;

    std::vector<int> leftArray(sizeLeft);
    std::vector<int> rightArray(sizeRight);

    for (int i = 0; i < sizeLeft; ++i)
        leftArray[i] = array[left + i];
    for (int j = 0; j < sizeRight; ++j)
        rightArray[j] = array[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < sizeLeft && j < sizeRight) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            ++i;
        }
        else {
            array[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < sizeLeft) {
        array[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < sizeRight) {
        array[k] = rightArray[j];
        ++j;
        ++k;
    }
}


void asyncMergeSort(std::vector<int>& array, int left, int right, int& maxThreads, int& activeThreads)
{
    std::mutex mutexActive;

    if (left < right) {
        int middle = left + (right - left) / 2;

        std::unique_lock<std::mutex> mutexLock(mutexActive);
        if (activeThreads < maxThreads && right - left > 10000) {
            ++activeThreads;
            mutexLock.unlock();

            std::future<void> leftFuture = std::async(std::launch::async, [&] {
                asyncMergeSort(array, left, middle, maxThreads, activeThreads);
                });
            std::future<void> rightFuture = std::async(std::launch::async, [&] {
                asyncMergeSort(array, middle + 1, right, maxThreads, activeThreads);
                });

            leftFuture.get();
            rightFuture.get();

            mutexLock.lock();
            --activeThreads;
        }
        else {
            mutexLock.unlock();

            asyncMergeSort(array, left, middle, maxThreads, activeThreads);
            asyncMergeSort(array, middle + 1, right, maxThreads, activeThreads);
        }

        merge(array, left, middle, right);
    }
}

int main() 
{

	int maxThreads = std::thread::hardware_concurrency();
	int activeThreads = 0;

	std::vector<int> mergeVector;

	const long size = 1000000;

	fillerFunc(mergeVector, size);

	asyncMergeSort(mergeVector, 0, mergeVector.size() - 1, maxThreads, activeThreads);

	return 0;
}
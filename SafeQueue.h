//
// Created by alvaro on 21/9/19.
//

#ifndef FRAMEOFREFERENCE_SAFEQUEUE_H
#define FRAMEOFREFERENCE_SAFEQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include "NormalQueue.h"

template <class T>
class SafeQueue{
private:
    NormalQueue<T>* queue;
    std::mutex mutex;
    std::condition_variable condVar;
public:

    SafeQueue();
    void push(T item);

    // Cuando esta vacia notifica al otro hilo
    T pop();

    void popFrontAndDelete();

    T getFront();

    bool empty();

    T front();

    ~SafeQueue();
};

template <class T>
SafeQueue<T>::SafeQueue() {
    this->queue = new NormalQueue<T>;
}

template <class T>
void SafeQueue<T>::push(T item){
    std::unique_lock<std::mutex> mlock(this->mutex);
    this->queue->push(item);
    mlock.unlock();
    this->condVar.notify_one();
}

template <class T>
T SafeQueue<T>::pop(){
    std::unique_lock<std::mutex> mlock(mutex);
    while (this->queue->isEmpty()){
        this->condVar.wait(mlock);
    }
    T element = this->queue->pop();
    mlock.unlock();
    this->condVar.notify_one();
    return element;
}

template <class T>
void SafeQueue<T>::popFrontAndDelete() {
    std::unique_lock<std::mutex> mlock(mutex);
    T* frontPtr = &(this->queue->front());
    delete *frontPtr;
    this->queue->pop();
}


//template <class T>
//T SafeQueue<T>::getFront(){
//    std::unique_lock<std::mutex> mlock(mutex);
//    while (this->queue->isEmpty()){
//        this->condVar.wait(mlock);
//    }
//    T object = this->queue->getFront();
//    return object;
//}

template <class T>
bool SafeQueue<T>::empty(){
    std::unique_lock<std::mutex> mlock(mutex);
    bool empty = this->queue->isEmpty();
    return empty;
}

template <class T>
T SafeQueue<T>::front(){
    std::unique_lock<std::mutex> mlock(mutex);
    return this->queue->getFront();
}

template <class T>
SafeQueue<T>::~SafeQueue() {
    std::unique_lock<std::mutex> mlock(mutex);
    delete(this->queue);
}


#endif //FRAMEOFREFERENCE_SAFEQUEUE_H

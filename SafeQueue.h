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
#include <atomic>

template <class T>
class SafeQueue{
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cvPush;
    std::condition_variable cvPop;
    unsigned int maxSize;
    std::atomic<bool> open;

public:
    //Se crea la cola con el tamaño maximo que puede soportar
    explicit SafeQueue(unsigned int maxSize);

    //Pushea si tiene espacio y manda una notificacion.
    void push(T& item);

    //Devuelve true si la cola esta llena
    bool queueIsFull();

    //Espera mientras la cola este vacia.
    // Devuelve el frente y luego lo elimina de la lista
    T pop();

    //Destructor vacio, todo en el stack.
    ~SafeQueue();
};

template <class T>
SafeQueue<T>::SafeQueue(unsigned int maxSize):maxSize(maxSize), open(true){}

template <class T>
void SafeQueue<T>::push(T& item){
    std::unique_lock<std::mutex> mlock(this->mutex);
    while (this->queueIsFull()) {
        this->cvPush.wait(mlock);
    }
    this->queue.push(item);
    mlock.unlock();
    this->cvPop.notify_all();
}


template <class T>
T SafeQueue<T>::pop(){
    std::unique_lock<std::mutex> mlock(mutex);
    while (this->queue.empty()){
        this->cvPop.wait(mlock);
    }
    T element = this->queue.front();
    this->queue.pop();
    mlock.unlock();
    this->cvPush.notify_all();
    return std::move(element);
}

template<class T>
bool SafeQueue<T>::queueIsFull() {
    std::atomic<bool> queueIsFull(false);
    queueIsFull = this->queue.size() == this->maxSize;
    return queueIsFull;
}



template <class T>
SafeQueue<T>::~SafeQueue() {}


#endif //FRAMEOFREFERENCE_SAFEQUEUE_H

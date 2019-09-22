#include <thread>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <sys/param.h>
#include <iomanip>
#include <queue>
#include <condition_variable>
#include "Vector.h"
#include "Controller.h"
#include <vector>

#include "Thread.h"
#include "FileProtected.h"
#include "SafeQueue.h"


void t1Process(Controller& controller) {
    controller.doDrill();
}


int main(){
    FileProtected file("pad", "data");
    clock_t start, end;
    int N=8;
    int amountOfThreads = 2;
    std::thread threads[2];
    Controller controller(&file, N);

    start = clock();

    while (!file.eof()) {
        for (int i = 0; i < amountOfThreads; ++i) {
            threads[i] = std::thread(t1Process, std::ref(controller));
        }
        for (int i = 0; i < amountOfThreads; ++i) {
            threads[i].join();
        }
    }
//        std::thread t1(t1Process, std::ref(controller));
//        std::thread t2(t1Process, std::ref(controller));
//
//        t1.join();
//        t2.join();

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed
         << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;
    return 0;
}


//SafeQueue<std::string> messages;
//std::string array[5] = {"Hola", "Gran", "dioso", "mundo", "querido"};
//std::mutex m;
//std::condition_variable cond_var;
//bool done = false;
//bool consumerNotified = false;
//bool producerNotified = false;
//
//void producer() {
//    std::unique_lock<std::mutex> lock(m);
//    for (int i = 0; i < 5; ++i) {
//        std::cout << "Sent: " << array[i] << std::endl;
//        messages.push(array[i]);
//        consumerNotified = true;
//        cond_var.notify_one();
//
//        cond_var.wait(lock, [&] { return producerNotified; });
//        producerNotified = false;
//    }
//
//    done = true;
//    cond_var.notify_one();
//}
//
//void consumer(){
//    std::unique_lock<std::mutex> lock(m);
//
//    while (!done) {
//        while (!consumerNotified && !done)
//            cond_var.wait(lock);
//
//        if (!messages.empty()) {
//            std::cout << "Received:" << messages.front() << '\n';
//            messages.pop();
//        }
//        producerNotified = true;
//        cond_var.notify_one();
//        consumerNotified = false;
//    }
//    std::cout << "Saliendo" << std::endl;
//}
//
//int main(){
//    auto ptrP = producer;
//    auto ptrC = consumer;
//
//    std::thread producer(ptrP);
//    std::thread consumer(ptrC);
//
//    producer.join();
//    consumer.join();
//}




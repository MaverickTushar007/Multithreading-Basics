#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>

std::condition_variable cv;
std::mutex mtx;
std::queue<int> dataQueue;

int ProduceCount = 10;
int consumeCount = 10;

void Producer() {
    while (ProduceCount != 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::unique_lock<std::mutex> lock(mtx);

            std::cout << "Producer:: adding data to the dataQueue" << std::endl;
            dataQueue.push(10);
        }

        cv.notify_one();
        ProduceCount--;
    }
}

void Consumer() {
    while(consumeCount != 0){
        std::unique_lock<std::mutex> lock(mtx);

        std::cout << "Consumer:: Waiting for data to arrive" << std::endl;

        cv.wait(lock, [] {
            return !dataQueue.empty();
        });

        int data = dataQueue.front();
        dataQueue.pop();

        std::cout << "data received: " << data << std::endl;
        consumeCount--;
    }
}

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::thread t1(Producer);
    std::thread t2(Consumer);

    t1.join();
    t2.join();

    return 0;
}
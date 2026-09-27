#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void Producer(std::promise<int> promise)
{
    std::this_thread::sleep_for(
        std::chrono::seconds(2));

    int data = 100;

    promise.set_value(data);
}

int main()
{
    std::promise<int> promise;

    std::future<int> future = promise.get_future();

    std::thread t(Producer, std::move(promise));

    std::cout << "Waiting for data...\n";

    int result = future.get();

    std::cout << "Data received: " << result << '\n';

    t.join();
}
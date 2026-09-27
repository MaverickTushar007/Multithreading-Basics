#include <iostream>
#include <thread>
#include <chrono>
#include <future>

std::promise<int> promise;

void Producer()
{
    std::cout << "Producer processing the request" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Data updated" << std::endl;

    promise.set_value(42);
}

std::thread DownloadData()
{
    return std::thread(Producer);
}

void ProcessRequest()
{
    // Get the future associated with the promise
    std::future<int> future = promise.get_future();

    std::cout << "Sending request to download data" << std::endl;

    // Start producer thread
    std::thread t2 = DownloadData();

    std::cout << "Waiting for the data from producer" << std::endl;

    // Blocks until Producer calls set_value()
    int data = future.get();

    std::cout << "Data received: " << data << std::endl;

    if (t2.joinable())
    {
        t2.join();
    }
}

int main()
{
    ProcessRequest();

    return 0;
}
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void add50Nu()
{
    int add50 = 0;
    for (int i = 0; i < 50; i++)
    {
        add50 += i;
    }
    cout << "add50: " << add50 << endl;
}

void add100Nu()
{
    int add100 = 0;
    for (int i = 0; i < 100; i++)
    {
        add100 += i;
    }
    cout << "add100: " << add100 << endl;
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

    start_time = std::chrono::system_clock::now();
    add50Nu();
    add100Nu();
    end_time = std::chrono::system_clock::now();
    cout << "Sequential Execution: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
            << " us" << endl;

    start_time = std::chrono::system_clock::now();
    std::thread t1(add50Nu);
    std::thread t2(add100Nu);
    t1.join();
    t2.join();
    end_time = std::chrono::system_clock::now();
    cout << "Thread Execution: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
            << " us" << endl;
}
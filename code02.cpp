#include <iostream>
#include <thread>

using namespace std;

void AddTwoNo(int x, int y)
{
    cout << "add: " << x + y << endl;
}

void MultiplyTwoNo(int x, int y)
{
    cout << "multi: " << x * y << endl;
}

int main()
{
    std::thread t1(AddTwoNo, 7, 4);
    std::thread t2(MultiplyTwoNo, 2, 2);

    t1.join();
    t2.join();
}
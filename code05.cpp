//DeadLocks

#include<iostream>
#include<thread>
#include<mutex>
std::mutex m1, m2;
using namespace std;

void function1(){
    m1.lock();
    cout<<"Thread ID: "<< std::this_thread::get_id()<<endl;
    m2.lock();
    cout<<"This is crtical Section"<<endl;
    m1.unlock();
    m2.unlock();
}

void function2(){
    m2.lock();
    cout<<"Thread ID: "<< std::this_thread::get_id()<<endl;
    m1.lock();
    cout<<"This is crtical Section"<<endl;
    m2.unlock();
    m1.unlock();
}
int main(){
    std::thread t1(function1);
    std::thread t2(function2);

    if(t1.joinable())
        t1.join();
    if (t2.joinable())
        t2.join();
}   

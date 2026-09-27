#include<iostream>
#include<thread>
using namespace std;

void fun1(){
    cout<<"called By thread_01"<<endl;
}
void fun2(){
    cout<<"called By thread_02"<<endl;
}
int main(){
    std::thread t1(fun1);
    std::thread t2(fun2);

    t1.join();
    t2.join();
}
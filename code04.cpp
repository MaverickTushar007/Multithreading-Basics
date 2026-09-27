#include <iostream>
#include <thread>

int shared_var = 0;


void function1(){
    shared_var ++;
    std::cout<<"value Printed: \t"<<shared_var<<std::endl;
}

int main(){

    std::thread threads[5];
    for (int i = 0; i<5;i++){
        threads[i] = std::thread(function1);
    }
    
    for (int i = 0; i<5;i++){
            threads[i].join();
    }
    
}
// Implementing a Task Executor in C++

#include<iostream>
#include<thread>
#include<queue>
#include<chrono>
#include<vector>
using namespace std;

std::queue<std::function<void()>> m_task;

bool isShutdown{false};
void addTaskToQueue(std::function<void()>fn){
    cout<<"Adding task to queue, thread Id: "<<std::this_thread::get_id()<<endl;
    m_task.push(fn);
}


class Executor{
    vector<std::thread> m_threads;
public: 
    //constructor: this thread will execute what function
    Executor(){
        m_threads.push_back(std::thread(&Executor::executeTask, this));
    }

    void executeTask(){
        while(true){
            if(!m_task.empty()){
                const auto& fn = m_task.front();
                fn();

                m_task.pop();
            }
            if(isShutdown) break;

        }
    }

    void shutdown(){
        cout<<"ShutDown Called"<<endl;
        isShutdown = true;
        for(auto& t: m_threads){
            if(t.joinable()){
                t.join();
            }
        }
    }
};

int main(){
    Executor exe;
    cout<<"Executor Object Created"<<endl;

    for(int itr = 0; itr<10; itr++){

        addTaskToQueue([](){
            cout<<"Lets submit the new order, thread Id: "<<std::this_thread::get_id()<<endl;
        });   
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    exe.shutdown();
}
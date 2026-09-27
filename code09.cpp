// HFT Systems Handle Market Data Feed Failover
#include<iostream>
#include<thread>
#include<atomic>
#include<chrono>

using namespace std;
/*
Assumptions:
    1. DataLine1 -> Primary feed source
    2. DataLine2 -> Secondary feed source
    3. Both threads continuously receive data
    4. Primary validates data
    5. If primary data is bad -> consumer switches to secondary
    6. Primary continues monitoring in background
    7. After a few coonsecutive good packets -> switch back to primary
*/

enum class FeedType{
    PRIMARY,
    SECONDARY
};

class MarkeDatFeedHandler{
    std::atomic<FeedType> activeFeed; //share among all the three threads
    std::atomic<int> primaryData{0};
    std::atomic<int> secondaryData{0};
    std::atomic<bool> running{true};

public:     
    bool validatePrimaryFeed(int value){
        return value%5 != 0; 
    }
    
    void primaryLine(){
        int value = 0;
        while(running){
            cout<<"data received over Primary Line \t"<<value<<endl;
            if (validatePrimaryFeed(value))
            {
                primaryData = value;
            }
            else{
                activeFeed = FeedType::SECONDARY;
                cout<<"Error: bad Primary data, switching to Secondary Data"<<endl;
            }
            std::this_thread::sleep_for(1s);
            value++;
        }
    }
    void secondaryLine(){
        int value = 100;
        while(running){
            secondaryData = value;
            value++;
            std::this_thread::sleep_for(1s);
        }
    }

    void dataConsumer(){
        while(running){
            if(activeFeed == FeedType::PRIMARY){
                std::cout<<"Consuming from the primary line, data = "<<primaryData<<endl;
            }
            else{
                std::cout << "Consuming from the secondary line, data = " << secondaryData << endl;
                activeFeed = FeedType::PRIMARY;
            }
            std::this_thread::sleep_for(1s);
        }

    }
    
    void stop()
    {
        running = false;
    }
};



int main(){
    MarkeDatFeedHandler system;
    std::thread t1(&MarkeDatFeedHandler::primaryLine, &system);
    std::thread t2(&MarkeDatFeedHandler::secondaryLine, &system);
    std::thread t3(&MarkeDatFeedHandler::dataConsumer, &system);

    std::this_thread::sleep_for(30s);

    system.stop();

    t1.join();
    t2.join();
    t3.join();
}
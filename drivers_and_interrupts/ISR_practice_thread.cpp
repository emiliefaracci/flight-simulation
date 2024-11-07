//write a program to simulate ISR, with multiple interuppt routines. 

#include <iostream>
#include <thread>
#include <atomic> 
#include <ctime> 
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

atomic<bool> InterruptOccured(false); 
atomic<int> InterruptType(0);

//in order to make sure the synch is working correctly 
mutex mtx;
condition_variable cv;

void ISR0 () {
    cout << "Interrupt0" << endl; 
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lock(mtx);
        InterruptOccured = false;
    }
    cv.notify_all();
}

void ISR1 () {
    cout << "Interrupt1" << endl; 
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lock(mtx);
        InterruptOccured = false;
    }
    cv.notify_all();
}

void ISR2 () {
    cout << "Interrupt2" << endl; 
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lock(mtx);
        InterruptOccured = false;
    }
    cv.notify_all();
}

void (*InterruptVector[])() = {ISR0, ISR1, ISR2};

void interruptGenerator() {

    //uses rand state generator to create an interrupt
    srand(time(nullptr));

    while (true) {
        InterruptType = rand() % 3;
        this_thread::sleep_for(chrono::seconds(1+ InterruptType));

        {
            lock_guard<mutex> lock(mtx);
            InterruptOccured = true; 
            cout << "Interrupt Generated: " << InterruptType << endl; 
        }

        InterruptVector[InterruptType]();
    }  
}

int main() {
    cout << "Experiment has started" << endl; 
    thread interruptThread(interruptGenerator);

    while (true) {

        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return InterruptOccured.load(); });

        if (InterruptOccured) {
            cout << "Currently dealing with interrupt" << endl; 
        } else {
            cout << "Main program running" << endl; 
            this_thread::sleep_for(chrono::milliseconds(300));
        }
    }
    
    interruptThread.join();
    return 0; 

}
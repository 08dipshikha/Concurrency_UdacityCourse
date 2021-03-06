#include <iostream>
#include <thread>

void threadFunc()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread work1 done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread work2 done" << std::endl;
}

int main()
{
    std::thread t(threadFunc);
    
    //call join here so main waits for thread to be completed
    t.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main work1 done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main work2 done" << std::endl;



    return 0;

}
//g++ file.cpp -pthread
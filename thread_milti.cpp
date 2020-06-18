#include <iostream>
#include <thread>

void threadFunc()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread func done" << std::endl;
}

int main()
{
    std::thread t(threadFunc);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main done" << std::endl;

    t.join();

    return 0;

}
//g++ file.cpp -pthread
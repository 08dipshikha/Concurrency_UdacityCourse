#include <iostream>
#include <thread>

void threadFunc()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread work done" << std::endl;
}

int main()
{
    std::thread t(threadFunc);

    t.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main work done" << std::endl;

    return 0;

}
//g++ file.cpp -pthread
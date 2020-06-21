#include <iostream>
#include <thread>
#include <vector>

void printHello()
{
    std::cout << "Hello from Worker Thread #" << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for(size_t i =0 ; i < 5; i++)
    {
        // copying thread objects causes a compile error
        /*
        std::thread t(printHello);
        threads.push_back(t); 
        */

        // moving thread objects will work
        threads.emplace_back(std::thread(printHello));
    }

    std::cout << "hello from main thread #" << std::this_thread::get_id()<< std::endl;

    for(auto &t : threads)
    {
        t.join();
    }
    return 0;
}

//output non deterministic nature and drawbacks from thread
#include <iostream>
#include <thread>
#include <vector>

int main()
{
    std::vector<std::thread> threads;
    for(size_t i = 0 ; i < 5; i++)
    {
        threads.emplace_back([i]() 
        {   
            std::this_thread::sleep_for(std::chrono::milliseconds(10*i));
            std::cout << "Hello from Worker thread #" << i << std::endl;
        });
    }

    std::cout << "Hello from main thread " << std::endl;

    for(auto &t : threads)
    {
        t.join();
    }
    return 0;
}
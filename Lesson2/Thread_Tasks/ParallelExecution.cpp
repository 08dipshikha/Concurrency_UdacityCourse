#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <chrono>
#include <future>

void workFunc(int n)
{
    std::cout << "Worker thread id:: " << std::this_thread::get_id() << std::endl;

    for(int i = 0; i<n; i++)
    {
        sqrt(12345.6789);
    }
}

int main()
{
    std::cout << "Main thread id:: " << std::this_thread::get_id() << std::endl;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::future<void>> futures;
    int nl = 100, nT = 5;
    for(int i=0; i<nT; i++)
    {
        futures.emplace_back(std::async(std::launch::deferred, workFunc, nl));
    }

    for(const std::future<void>& ftr : futures)
    {
        ftr.wait();
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout <<"execution time  " << duration << std::endl;

    return 0;
} 
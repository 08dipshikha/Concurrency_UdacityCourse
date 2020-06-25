#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divByNum(double num, double den)
{
    std::cout << "Worker thread id:: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(den == 0)
    {
        throw std::runtime_error("Denom zero:: exception from worker thread");
    }
    return num/den;
}

int main()
{
    std::cout<< "In main thread id::  " << std::this_thread::get_id() << std::endl;

    double num = 42.0, denom = 2.0;

    std::future<double> ftr = std::async(std::launch::async, divByNum, num, denom);
        //std::launch::async diff threads , any for system choice
    try
    {
        double result = ftr.get();
        std::cout << "result  " << result << std::endl;
    }
    catch(const std::runtime_error e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
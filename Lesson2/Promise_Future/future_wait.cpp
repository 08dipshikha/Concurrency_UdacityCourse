#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void compSqrt(std::promise<double> &&prms, double ip)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    double op = sqrt(ip);
    prms.set_value(op);
}

int main()
{
    double input = 42;
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();
    std::thread t(compSqrt, std::move(prms), input);

    auto status = ftr.wait_for(std::chrono::milliseconds(1000));
    if(status == std::future_status::ready)
    {
        std::cout << "Result  " << ftr.get() << std::endl;
    }
else if (status == std::future_status::timeout || status == std::future_status::deferred)
    {
        std::cout << "Result unavailable" << std::endl;
    }

    // thread barrier
    t.join();

    return 0;
}
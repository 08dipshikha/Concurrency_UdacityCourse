#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <algorithm>
class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID() { return _id;}  
private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() {}
    void printIDs()
    {
        std::lock_guard<std::mutex> lck1(_mtx);
        for(auto &v: _vehicles)
        {
            std::cout << "printID:: vehicle id is #" << v.getID() << std::endl;
        }
    }

    void pushBack(Vehicle &&v)
    {
        std::lock_guard<std::mutex> lck2(_mtx);
        std::cout << "pushBack:: vehicle id is #" << v.getID() << std::endl;
        _vehicles.emplace_back(std::move(v));

        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

private:
    std::vector<Vehicle> _vehicles;
    std::mutex _mtx;
};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads .... " << std::endl;
    std::vector<std::future<void>> ftrs;
    for(int i=0; i < 10 ; i++)
    {
        Vehicle v(i);
        ftrs.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(ftrs.begin(), ftrs.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    std::cout << "Collecting results..." << std::endl;
    queue->printIDs();

    return 0;
}
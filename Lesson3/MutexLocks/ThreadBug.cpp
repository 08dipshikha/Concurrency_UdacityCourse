#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() : _tmpVehicles(0) {}
    void printSize()
    {
        std::cout << "Number of vehicles #" << _tmpVehicles << std::endl;
    }

    void pushBack(Vehicle &&v)
    {
        //_vehicles.push_back(std::move(v));
        int oldNum = _tmpVehicles;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        _tmpVehicles = oldNum+1;
    }
private:
    int _tmpVehicles;
    std::vector<Vehicle> _vehicles;

};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void>> futures;
    for(int i = 0; i < 1000; i++)
    {
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr){
        ftr.wait();
    });

    queue->printSize();
    return 0;
}
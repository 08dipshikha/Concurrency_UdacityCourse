#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
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
    Vehicle popBack()
    {
        std::unique_lock<std::mutex> lck1(_mtx);
        _cond.wait(lck1, [this] { return !_vehicles.empty();});

        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back();
        return v;
    }

    void pushBack(Vehicle &&v)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::lock_guard<std::mutex> lck2(_mtx);

        std::cout << "vehicle #" << v.getID() << std::endl;
        _vehicles.push_back(std::move(v));
        _cond.notify_one();
    }


private:
    std::mutex _mtx;
    std::condition_variable _cond;
    std::vector<Vehicle> _vehicles;
};
int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::cout << "Collecting results..." << std::endl;
    while (true)
    {
        // popBack wakes up when a new element is available in the queue
        Vehicle v = queue->popBack();
        std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    std::cout << "Finished!" << std::endl;

    return 0;
}
#include <iostream>
#include <thread>
#include <memory>

class Vehicle
{
    public:
        Vehicle() : _id(0) {}
        void addID(int id) { _id = id; }
        void printId()
        {
            std::cout << "Vehicle id is " << _id << std::endl;
        }
    private:
        int _id;
};

int main()
{
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::addID, v, 2);

    t.join();

    v->printId();

    return 0;
}
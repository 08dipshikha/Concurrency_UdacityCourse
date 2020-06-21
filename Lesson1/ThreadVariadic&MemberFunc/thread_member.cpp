#include <iostream>
#include <thread>

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
    Vehicle v1, v2;
    std::thread t1 = std::thread(&Vehicle::addID, v1, 1);
    std::thread t2 = std::thread(&Vehicle::addID, &v2, 2);

    t1.join();
    t2.join();

    v1.printId();
    v2.printId();

    return 0;
}
#include <iostream>
#include <thread>

class Vehicle
{
    public:
        Vehicle(int id): _id(id) {}
        void operator()()
        {
            std::cout << "Vehicle # " << _id << " created" << std::endl;
        }
    private:
        int _id;
};

int main()
{
    std::thread t1 = std::thread(Vehicle(1));

    std::cout << "Main created " << std::endl;

    t1.join();
    return 0;
}
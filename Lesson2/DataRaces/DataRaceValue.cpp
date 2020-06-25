#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
public:
    Vehicle() : _id(0)
    {
        std::cout << "Def vehicle id # " << _id << std::endl;
    }
    Vehicle(int id) : _id(id)
    {
        std::cout << "Ini Cons vehicle id # " << _id << std::endl;
    }
    void setID(int id) { _id = id;}
    int getID() {return _id;}
    
private:
    int _id;
};

int main()
{
    Vehicle v0;
    Vehicle v1(10);

    std::future<void> ftr = std::async([](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        v.setID(20);
    },v0) ;

    v0.setID(3);
    ftr.wait();

    std::cout << "Main vehicle id # " << v0.getID() << std::endl;
    return 0;
}
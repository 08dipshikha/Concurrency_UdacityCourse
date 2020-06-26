#include <iostream>
#include <thread>
#include <future>
#include <memory>

class Vehicle
{
public:
    Vehicle() : _id(0), _name(new std::string("defualt name"))
    {
        std::cout << "Vehicle id #" << _id << " default constructor"<< std::endl;
    }
    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
    {
        std::cout << "Vehicle id #" << _id << " initialize constructor"<< std::endl;

    }
    //move const
    Vehicle(Vehicle &&src) : _name(std::move(src._name))
    {
        _id = src.getID();
        src.setID(0);
        std::cout << "Vehicle id #" << _id << " move constructor"<< std::endl;
    }

    void setID(int id) { _id = id;}
    int getID() { return _id;}
    void setName(std::string name) { *_name = name;}
    std::string getName() { return *_name;}
private:
    int _id;
    std::unique_ptr<std::string> _name; 
};

int main()
{
    Vehicle v0;
    Vehicle v1(1,"Vehicle 1");

    std::future<void> ftr = std::async([](Vehicle v)
    {
        v.setID(2);
        v.setName("vehicle 2");
    },std::move(v0));

    ftr.wait();
    //std::cout << v0.getName() << std::endl;

    return 0;

}
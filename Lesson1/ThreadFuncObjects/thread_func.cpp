#include <iostream>
#include <thread>

class Vehicle
{
    public:
        void operator()()
        {
            std::cout << "vehicle created " << std::endl;
        }
};

int main()
{
    std::thread t1( (Vehicle()) ); //Add an extra pair of parantheses
    std::thread t2 = std::thread( (Vehicle()) ); // Use copy initialization
    std::thread t3{ Vehicle() }; // Use uniform initialization with braces
    std::cout << "Main done " << std::endl;

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
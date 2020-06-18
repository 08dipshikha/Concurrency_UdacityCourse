#include <iostream>
#include <thread>

int main()
{
    unsigned int ncores = std::thread::hardware_concurrency();
    std::cout << "Machine supports cores available : " << ncores << std::endl;
}
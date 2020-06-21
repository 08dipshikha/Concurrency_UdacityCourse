#include <thread>
#include <iostream>

int main()
{
    std::cout << "Thread id:  " << std::this_thread::get_id() << std::endl;
}
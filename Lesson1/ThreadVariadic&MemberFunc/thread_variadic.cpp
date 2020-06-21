#include <iostream>
#include <thread>
#include <string>


void printId(int id)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "ID is " << id << std::endl;
}

void printIdName(int id, std::string name)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "id is  " << id << " and name is " << name << std::endl;

}

int main()
{
    int id = 0;
    std::thread t1(printId, id);
    std::thread t2(printIdName, ++id, "String");

    t1.join();
    t2.join();

    return 0;
}
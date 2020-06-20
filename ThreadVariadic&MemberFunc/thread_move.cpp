#include <iostream>
#include <string>
#include <thread>

void printName(std::string name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name is " << name << std::endl;
}

int main()
{
    std::string s1 = "Thread1";
    std::string s2 = "Thread2";

    std::thread t1(printName, s1, 50);
    std::thread t2(printName, std::move(s2),100);

    t1.join();
    t2.join();

    std::cout << "name 1 is " << s1 << std::endl;
    std::cout << "name 2 is " << s2 << std::endl;

    return 0;
}
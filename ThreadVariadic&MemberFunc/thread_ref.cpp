#include <iostream>
#include <string>
#include <thread>

void printname(std::string &name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    name+= "(from Thread)";
    std::cout << name << std::endl;
}

int main()
{
    std::string name("My Thread");
    std::thread t(printname,std::ref(name),50);

    t.join();
    name+= "(from Main)";
    std::cout << name << std::endl;

    return 0;

}
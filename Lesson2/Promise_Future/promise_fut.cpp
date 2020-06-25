#include <iostream>
#include <thread>
#include <future>

void ModMsg(std::promise<std::string> &&prms, std::string msg)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::string modify = msg + " Adding on it";
    prms.set_value(modify);
}
int main()
{
    std::string msg = "MyMsg";

    //create future and promise
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    std::thread t(ModMsg, std::move(prms), msg);
    std::cout << "Ori msg " << msg << std::endl;

    std::string rcv_msg = ftr.get();
    std::cout << "Mod msg " << rcv_msg << std::endl;

    //thread barrier
    t.join();

    return 0;



}
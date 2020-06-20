#include <iostream>

int main()
{
    int id_ = 2;

    auto f = [](const int id) { std::cout << "Id is " << id << std::endl; };

    f(id_);
    return 0;
}
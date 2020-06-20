#include<iostream>

int main()
{
    int id = 0;
    //auto f0 = []() { std::cout << " ID is " << id << std::endl; };  //id can't be accessed
    id++;
    auto f1 = [id]() { std::cout << " ID is " << id << std::endl; } ; //by value

    id++;
    auto f2 = [&id]() { std::cout << " ID is " << id << std::endl; }; //by reference

    //auto f3 = [id]() { std::cout << " ID is " << id++<< std::endl; }; //cannot modify

    auto f4 = [id]() mutable { std::cout << " ID is " << ++id << std::endl; }; //can be modified

    f1();
    f2();
    f4();
    return 0;
    
}
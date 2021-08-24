#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <random>

///////////////
//

int GetRandomInt(int minVal, int maxVal)
{
    std::random_device rd;
    static std::mt19937 ms(rd());
    std::uniform_int_distribution<> uid(minVal, maxVal);
    return uid(ms);
}

///////////////
// Задача 1

void Task1()
{
    std::cout << "Задача 1." << std::endl;
}

///////////////
// Задача 2

void Task2()
{
    std::cout << std::endl << "Задача 2." << std::endl;
}

int main()
{
    Task1();
    Task2();

    return 0;
}

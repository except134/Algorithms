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

class Stack
{
public:
    Stack(){};

    ~Stack()
    {
        if (count > 0)
            delete[] data;
    }

    void Push(int val)
    {
        int* temp = data;
        data = new int[count + 1];
        count++;

        for (int i = 0; i < count - 1; i++)
            data[i] = temp[i];

        data[count - 1] = val;

        if (count > 1)
            delete[] temp;
    }

    int Pop()
    {
        if (count == 0)
            return 0;
        count--;
        return data[count];
    }

    void Print()
    {
        int* temp = data;

        if (count == 0)
            std::cout << "Стек пустой." << std::endl;

        for (int i = 0; i < count; i++) {
            std::cout << *temp++;
        }
        std::cout << std::endl;
    }
private:
    int* data{};
    int count = 0;
};

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

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

    int Peek()
    {
        if (count == 0)
            return 0;
        return data[count - 1];
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

class Graf
{
public:
    Graf() = default;

    ~Graf()
    {
        for(int index = 0; index < count; ++index) {
            delete[] graf[index];
        }
        delete[] graf;
    }

    void Init(int n, int m)
    {
        count = n;

        if(m > n * (n - 1) / 2) {
            std::cout << "Слишком много граней." << std::endl;
            return;
        }

        graf = new int*[n];
        for(int index = 0; index < n; ++index) {
            graf[index] = new int[n];
        }

        while(m) {
            for(int i = 0; i < n && m; ++i) {
                for(int j = i + 1; j < n && m; ++j) {
                    int v = GetRandomInt(0,10) > 3 ? 1 : 0;
                    if (v && !graf[i][j]) {
                        graf[i][j] = graf[j][i] = v;
                        m--;
                    }
                }
            }
        }
    }

    void Print()
    {
        for(int i = 0; i < count; ++i) {
            for(int j = 0; j < count; ++j) {
                std::cout << graf[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    int** graf{nullptr};
    int count=0;
};

///////////////
// Задача 1

void Task1()
{
    std::cout << "Задача 1." << std::endl;

    Graf graf;
    graf.Init(5, 7);
    graf.Print();
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

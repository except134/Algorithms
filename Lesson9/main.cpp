#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>

///////////////
// Задача 1

class Node
{
public:
    Node(){}
    Node(int p, int d) : priority(p), data(d) {}

    Node(const Node& other)
    {
        priority = other.priority;
        data = other.data;
    }

    Node& operator=(const Node& other)
    {
        priority = other.priority;
        data = other.data;

        return *this;
    }

    int priority = 0;
    int data = 0;
};

class Queue
{
public:
    Queue(){}

    ~Queue()
    {
        if(count > 0)
            delete[] queue;
    };

    Queue(const Queue& other)
    {
        queue = new Node[other.count];
        count = other.count;

        for (int i = 0; i < count; ++i)
            queue[i] = other.queue[i];
    }

    Queue& operator=(const Queue& other)
    {
        if(count > 0) {
            delete[] queue;
            count = 0;
        }

        queue = new Node[other.count];
        count = other.count;

        for (int i = 0; i < count; ++i)
            queue[i] = other.queue[i];

        return *this;
    }

    void Push(int priority, int data)
    {
        Node val(priority, data);

        Node* temp = new Node[count+1];
        for (int i = 0; i < count; ++i)
            temp[i] = queue[i];
        temp[count] = val;

        if(count > 0)
            delete[] queue;

        count++;
        queue = temp;
    }

    Node Pop()
    {
        if(count == 0)
            return {-1, -1};

        int maxIndex = 0;
        int maxPriority = queue[0].priority;

        for(int i = 0; i < count; ++i) {
            if(queue[i].priority > maxPriority) {
                maxPriority = queue[i].priority;
                maxIndex = i;
            }
        }

        Node ret = queue[maxIndex];

        Node* temp = new Node[count-1];
        for (int i = 0, j = 0; i < count; ++i) {
            if(i != maxIndex)
                temp[j++] = queue[i];
        }

        if(count > 0)
            delete[] queue;

        queue = temp;
        count--;

        return ret;
    }

    void Print()
    {
        std::cout << "Очередь: " << std::endl;
        for (int i = 0; i < count; i++)
            std::cout << "Число = " << queue[i].data << " : " << " приоритет = " << queue[i].priority << std::endl;
        std::cout << std::endl;
    }

private:
    Node* queue{};
    int count = 0;
};

void Task1()
{
    std::cout << "Задача 1." << std::endl;

    Queue queue;
    queue.Push(7, 1);
    queue.Push(9, 2);
    queue.Push(5, 3);
    queue.Push(4, 4);
    queue.Push(3, 5);
    queue.Push(2, 6);
    queue.Push(1, 7);
    queue.Print();

    queue.Pop();
    queue.Pop();
    queue.Print();

    queue.Push(112, 66);
    queue.Push(12, 33);
    queue.Print();

    queue.Pop();
    queue.Print();
}

///////////////
// Задача 2

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

void Dec2Bin(unsigned int num, Stack& stack)
{
    if(num) {
        Dec2Bin(num >> 1, stack);
        stack.Push(num & 1);
    }
}

void Task2()
{
    unsigned int num{};

    std::cout << "Задача 2." << std::endl;
    std::cout << "Введите число: ";
    std::cin >> num;

    Stack stack;
    Dec2Bin(num, stack);

    std::cout << "Число " << num << " в двоичной системе счисления: ";
    stack.Print();
}

int main()
{
    Task1();
//    Task2();

    return 0;
}

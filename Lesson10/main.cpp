#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

///////////////
// Задача 1

struct Brace
{
    char left;
    char right;
    int count;
    void ResetCount() { count = 0; }
};

bool CheckStringCorrectness(const char* str, Brace braces[], int size)
{
    for(int j = 0; j < size; j++) {
        braces[j].ResetCount();
    }

    for(int i = 0; i < strlen(str); i++) {
        char c = str[i];
        for(int j = 0; j < size; j++) {
            if(c == braces[j].left)
                braces[j].count++;
            else if(c == braces[j].right)
                braces[j].count--;
        }
    }

    int temp =0;

    for(int j = 0; j < size; j++) {
        temp += braces[j].count;
    }

    return temp != 0 ? false : true;
}

void TestString(const char* str, Brace braces[], int size)
{
    std::cout << "Строка " << str << " ";
    if(CheckStringCorrectness(str, braces, size))
        std::cout << "корректна." << std::endl;
    else
        std::cout << "не корректна." << std::endl;
}

void Task1()
{
    const char* correctString="[2/{5*(4+7)}]";
    const char* uncorrectString="[2/{5*(4+7))}]";
    const char* uncorrectString2="]2/{5*(4+7))}]";
    const char* correctString2="(), ([])(), {}(), ([{}])";
    const char* uncorrectString3=")(, ())({), (, ])}), ([(])";

    Brace braces[]={
            {'(', ')', 0},
            {'[', ']', 0},
            {'{', '}', 0},
            {'<', '>', 0},
    };

    std::cout << "Задача 1." << std::endl;

    int bracesSize = sizeof(braces)/sizeof(braces[0]);

    TestString(correctString, braces, bracesSize);
    TestString(uncorrectString, braces, bracesSize);
    TestString(uncorrectString2, braces, bracesSize);
    TestString(correctString2, braces, bracesSize);
    TestString(uncorrectString3, braces, bracesSize);
}

///////////////
// Задача 2

void Task2()
{
    std::cout << std::endl << "Задача 2." << std::endl;
}

///////////////
// Задача 3

void Task3()
{
    std::cout << std::endl << "Задача 3." << std::endl;
}

int main()
{
    Task1();
    Task2();
    Task3();

    return 0;
}

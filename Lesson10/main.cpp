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

struct Node
{
    int data = 0;
    struct Node* next{ nullptr };
};

struct List
{
    Node* head{ nullptr };
    int size = 0;
};

void AddListValue(List* list, int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->data = val;
    temp->next = list->head;

    list->head = temp;
    list->size++;
}

void FillListRandom(List* list, int count)
{
    for(int i = 0; i < count; i++)
        AddListValue(list, rand()%100);
}

void PrintList(List* list)
{
    if(list->head == nullptr || list->size == 0) {
        std::cout << std::endl;
        return;
    }

    Node* current = list->head;

    do {
        std::cout << current->data << " ";
        current = current->next;
    } while (current != nullptr);

    std::cout << std::endl;
}

void CopyList(List* src, List* dst)
{
    if(src->head == nullptr || src->size == 0) {
        return;
    }

    Node* current = src->head;

    do {
        AddListValue(dst, current->data);
        current = current->next;
    } while (current != nullptr);
}

void Task2()
{
    std::cout << std::endl << "Задача 2." << std::endl;

    srand(time(0));

    List list1, list2;
    FillListRandom(&list1, 10);
    std::cout << "Список 1: ";
    PrintList(&list1);

    std::cout << "Копируем список 1 в список 2." << std::endl;

    CopyList(&list1, &list2);

    std::cout << "Список 2: ";
    PrintList(&list2);

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

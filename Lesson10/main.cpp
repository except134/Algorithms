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

class Node
{
public:
    Node(int val) : data(val) {}

public:
    int data = 0;
    Node* next{ nullptr };
};

class List
{
public:
    ~List()
    {
        Node* p = head;
        while (p) {
            Node* t = p;
            p = p->next;
            delete t;
        }
    }

    bool IsEmpty() { return head == nullptr; }

    void Push(int val)
    {
        Node* p = new Node(val);
        if (IsEmpty()) {
            head = p;
            tail = p;
            return;
        }
        tail->next = p;
        tail = p;
    }

    void Print(bool printEOL = true)
    {
        if (IsEmpty())
            return;

        Node* p = head;
        while (p) {
            std::cout << p->data << " ";
            p = p->next;
        }

        if(printEOL)
            std::cout << std::endl;
    }

    void CopyTo(List* list)
    {
        if (IsEmpty())
            return;

        Node* p = head;
        while (p) {
            list->Push(p->data);
            p = p->next;
        }
    }

    void Sort()
    {
        Node *firstNum, *secondNum, *ptr, *hdr = nullptr;

        for(Node* i = head; i != nullptr; ) {
            firstNum = i;
            i = i->next;
            secondNum = hdr;
            for(ptr = nullptr; (secondNum != nullptr) && (firstNum->data > secondNum->data); ) {
                ptr = secondNum;
                secondNum = secondNum->next;
            }

            if(ptr == nullptr) {
                firstNum->next = hdr;
                hdr       = firstNum;
            } else {
                firstNum->next = secondNum;
                ptr->next = firstNum;
            }
        }
        if(hdr != nullptr)
            head = hdr;
    }

    bool IsEqual(List* list)
    {
        Node* curVal = head;
        Node* dstVal = list->head;

        while (curVal) {
            if(curVal->data != dstVal->data)
                return false;

            curVal = curVal->next;
            dstVal = dstVal->next;
        }

        return true;
    }

    bool IsSort()
    {
        List temp;
        CopyTo(&temp);

        temp.Sort();
        return IsEqual(&temp);
    }

private:
    Node* head{ nullptr };
    Node* tail{ nullptr };
};

void FillListRandom(List* list, int count)
{
    for(int i = 0; i < count; i++)
        list->Push(rand()%100);
}

void Task2()
{
    std::cout << std::endl << "Задача 2." << std::endl;

    srand(time(0));

    List list1, list2;
    FillListRandom(&list1, 10);
    std::cout << "Список 1: ";
    list1.Print();

    std::cout << "Копируем список 1 в список 2." << std::endl;

    list1.CopyTo(&list2);

    std::cout << "Список 2: ";
    list2.Print();
}

///////////////
// Задача 3

void Task3()
{
    std::cout << std::endl << "Задача 3." << std::endl;

    srand(time(0));

    List list;
    FillListRandom(&list, 10);

    std::cout << "Список: ";
    list.Print(false);
    std::cout << (list.IsSort() ? "отсортирован." : "не отсортирован") << std::endl;

    std::cout << "Сортируем" << std::endl;
    list.Sort();

    std::cout << "Список: ";
    list.Print(false);
    std::cout << (list.IsSort() ? "отсортирован." : "не отсортирован") << std::endl;
}

int main()
{
    Task1();
    Task2();
    Task3();

    return 0;
}

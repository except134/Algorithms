#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

class Node
{
public:
    Node() = default;
    Node(int k) : key(k) {}

    void GetHeight()
    {
        key = 0;
        if (left != nullptr) {
            left->GetHeight();
            key = std::max(key, left->key + 1);
        }
        if (right != nullptr) {
            right->GetHeight();
            key = std::max(key, right->key + 1);
        }
    }
    
public:
    int key = 0;
    Node* left{nullptr};
    Node* right{nullptr};
};

class Tree
{
public:
    Tree() = default;

    ~Tree()
    {
        DestroyNode(root);
    }

    void Insert(int x)
    {
        Node** cur = &root;
        while (*cur) {
            Node& node = **cur;
            if (x < node.key) {
                cur = &node.left;
            } else if (x > node.key) {
                cur = &node.right;
            } else {
                return;
            }
        }
        *cur = new Node(x);
    }

private:
    static void DestroyNode(Node* node)
    {
        if(node) {
            DestroyNode(node->left);
            DestroyNode(node->right);
            delete node;
        }
    }

private:
    Node* root{nullptr};
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

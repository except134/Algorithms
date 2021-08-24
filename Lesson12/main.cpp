#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <random>

class Node
{
public:
    Node() = default;
    Node(int val) : value(val) {}
    ~Node() = default;

    bool IsRight() const
    {
        return ((parent == nullptr) || (parent->right != this)) ? false : true;
    }

    bool IsLeft() const
    {
        return ((parent == nullptr) || (parent->left != this)) ? false : true;
    }

    void Print(int level = 0)
    {
        const Node* cur = this;

        if(cur != nullptr)
            cur->right->Print(level + 1);

        for(int spaces = 0; spaces < level; ++spaces)
            std::cout << "    ";

        if(cur != nullptr)
            std::cout << cur->value << '[' << cur->count << ']' << std::endl;
        else
            std::cout << "+" << std::endl;

        if(cur != nullptr)
            cur->left->Print(level + 1);
    }

public:
    int value{0};
    int count{1};
    Node* left{nullptr};
    Node* right{nullptr};
    Node* parent{nullptr};
};

class Tree
{
public:
    Tree() = default;

    Tree(int val) : zero(nullptr)
    {
        MakeNewRoot(val);
    }

    ~Tree()
    {
        Cleanup(root);
    }

    bool Add(int val)
    {
        Node* ret = Insert(val);

        return ret ? true : false;
    }

    void Remove(int val)
    {
        Node*& nodeToRemove = FindNode(val);
        Node* predecessor = nullptr;
        Node* temp = nullptr;

        if(nodeToRemove == zero)
            return;

        if(nodeToRemove->left == nullptr) {
            temp = nodeToRemove;

            if(nodeToRemove->right != nullptr) {
                nodeToRemove->right->parent = nodeToRemove->parent;
            }

            nodeToRemove = nodeToRemove->right;
            AdjustCountToRoot(temp->parent, -1);
            delete temp;
            return;
        } else if(nodeToRemove->right == nullptr) {
            temp = nodeToRemove;

            nodeToRemove->left->parent = nodeToRemove->parent;

            nodeToRemove = nodeToRemove->left;
            AdjustCountToRoot(temp->parent, -1);
            delete temp;
            return;
        }

        predecessor = nodeToRemove->left;

        while (predecessor->right != nullptr)
            predecessor = predecessor->right;

        nodeToRemove->value = predecessor->value;

        Node* pp = predecessor->parent;

        if(pp==nodeToRemove) {
            pp->left = predecessor->left;
            if(predecessor->left != nullptr)
                predecessor->left->parent = pp;
        } else if(predecessor->left != nullptr) {
            pp->right = predecessor->left;
            predecessor->left->parent = pp;
        } else {
            pp->right = nullptr;
        }

        AdjustCountToRoot(pp, -1);

        delete predecessor;
    }

    int Get(int index)
    {
        Node* cur = GetNode(root, index);
        return cur->value;
    }

    int Size() const
    {
        return root ? root->count : 0;
    }

    bool Find(int val)
    {
        Node* cur = FindNode(val);

        return cur != nullptr ? true : false;
    }

    void Print()
    {
        std::cout << "\n-----------------------------------------------------------\n" << std::endl;
        root->Print();
    }

    void PrintPre()
    {
        PrintPre(root);
        std::cout << std::endl;
    }

    void PrintIn()
    {
        PrintIn(root);
        std::cout << std::endl;
    }

    void PrintPost()
    {
        PrintPost(root);
        std::cout << std::endl;
    }

    int GetRootCount() const
    {
        return Size();
    }

    int GetLeftCount() const
    {
        return root->left ? root->left->count : 0;
    }

    int GetRightCount() const
    {
        return root->right ? root->right->count : 0;
    }

private:
    void MakeNewRoot(int val)
    {
        root = new Node(val);
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
        root->count = 1;
    }

    Node*& FindNode(int val)
    {
        Node* cur = root;

        while((cur != nullptr) && (cur->value != val)) {
            cur = val < cur->value ? cur->left : cur->right;
        }

        if(cur == nullptr)
            return zero;
        else if(cur->IsLeft())
            return cur->parent->left;
        else if(cur->IsRight())
            return cur->parent->right;
        else if(cur == root)
            return root;

        return zero;
    }

    Node* Insert(int val, Node* start = nullptr)
    {
        if(root == nullptr) {
            MakeNewRoot(val);
            return root;
        }

        if(start == nullptr)
            start = root;

        Node* cur = start;

        while((cur != nullptr) /*&& (cur->value != val)*/) {
            if(val < cur->value) {
                if(cur->left == nullptr) {
                    Attach(cur, cur->left, val);
                    AdjustCountToRoot(cur, 1);
                    return cur->left;
                } else {
                    cur = cur->left;
                }
            } else {
                if(cur->right == nullptr) {
                    Attach(cur, cur->right, val);
                    AdjustCountToRoot(cur, 1);
                    return cur->right;
                } else {
                    cur = cur->right;
                }
            }
        }

        return nullptr;
    }

    void Attach(Node* newParent, Node*& newChild, int val)
    {
        newChild = new Node(val);
        newChild->parent = newParent;
    }

    void AdjustCountToRoot(Node* node, int incr)
    {
        while(node != nullptr) {
            node->count += incr;
            node = node->parent;
        }
    }

    Node* GetNode(Node* node, int index)
    {
        if(node == nullptr)
            return nullptr;

        int leftCount = (node->left != nullptr) ? node->left->count : 0;

        if((leftCount + 1) == index) {
            return node;
        } else if(leftCount >= index) {
            return GetNode(node->left, index);
        } else {
            return GetNode(node->right, index - leftCount - 1);
        }
    }

    void Cleanup(Node* node)
    {
        if(node == nullptr)
            return;

        if(node->left != nullptr) {
            Cleanup(node->left);
            node->left = nullptr;
        }

        if(node->right != nullptr) {
            Cleanup(node->right);
            node->right = nullptr;
        }

        delete node;
    }

    void PrintPre(const Node* node)
    {
        if(node == nullptr)
            return;

        std::cout << node->value << " ";

        if(node->left != nullptr)
            PrintPre(node->left);

        if(node->right != nullptr)
            PrintPre(node->right);
    }

    void PrintIn(const Node* node)
    {
        if(node == nullptr)
            return;

        if(node->left != nullptr)
            PrintIn(node->left);

        std::cout << node->value << " ";

        if(node->right != nullptr)
            PrintIn(node->right);
    }

    void PrintPost(const Node* node)
    {
        if(node == nullptr)
            return;

        if(node->left != nullptr)
            PrintPost(node->left);

        if(node->right != nullptr)
            PrintPost(node->right);

        std::cout << node->value << " ";
    }

private:
    Node* root{nullptr};
    Node* zero{nullptr};
};

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
    const int COUNT_OF_TREES = 50;
    const int COUNT_OF_NUMBERS = 10000;

    std::cout << "Задача 1." << std::endl;

    Tree trees[COUNT_OF_TREES];

    int balanced = 0;

    for(int t = 0; t < COUNT_OF_TREES; t++) {
        for(int i = 0; i < COUNT_OF_NUMBERS; i++) {
            trees[t].Add(GetRandomInt(0,10000000));
        }

        std::cout << "Дерево " << t+1 << ": слева = " << trees[t].GetLeftCount();
        std::cout << ", справа = " << trees[t].GetRightCount();
        std::cout << ", всего = " << trees[t].GetRootCount() << std::endl;

        // За разницу берем 1000, чисто для теста, так как шансов, что выпадет сбалансированное дерево крайне мало.
        if(std::abs(trees[t].GetLeftCount() - trees[t].GetRightCount()) <= 1000)
            balanced++;
    }

    std::cout << "Сбалансированных деревьев:  " << balanced << std::endl;
    std::cout << "Не сбалансированных деревьев:  " << COUNT_OF_TREES - balanced << std::endl;

    std::cout << "Процент сбалансированных деревьев:  " << (balanced * 100 / COUNT_OF_TREES) << std::endl;

}

///////////////
// Задача 2

void Task2()
{
    std::cout << std::endl << "Задача 2." << std::endl;

    const int COUNT_OF_NUMBERS = 10;

    Tree t;

    for(int i = 0; i < COUNT_OF_NUMBERS; i++) {
        t.Add(GetRandomInt(0,100));
    }

    t.Print();

    unsigned int num = 0;
    std::cout << "Введите число для поиска: ";
    std::cin >> num;

    std::cout << "Число " << num;

    if(t.Find(num)) {
        std::cout << " найдено." << std::endl;
    } else {
        std::cout << " не найдено." << std::endl;
    }

}

int main()
{
    Task1();
    Task2();

    return 0;
}

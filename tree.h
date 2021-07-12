#include <QApplication>
#ifndef TREE_H
#define TREE_H
#define MAX 1000

class Node
{
public:
    int data;
    Node* childern[MAX];

    Node(int val);
    ~Node();

};

class Tree
{
public:
    Tree();
    ~Tree();
    void insert(int val);

};

#endif // TREE_H

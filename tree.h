#include <QApplication>
#ifndef TREE_H
#define TREE_H

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }

    ~Node()
    {
        delete this;
        delete [] left;
        delete [] right;

    }
};

class Tree
{
public:
    Tree();
};

#endif // TREE_H

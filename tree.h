#include <QApplication>
#ifndef TREE_H
#define TREE_H
#define MAX 1000
#include "qlist.h"
#include "qvector.h"
class Node
{
public:
    int data;
    QVector<Node*> childern;
    Node(int val);
    ~Node();

};

class Tree
{
private:
    Node* root;
public:
    Tree();
    ~Tree();
    void insert (Node* leaf , int val, int parent);
    void insert(int val , int parent);
    void postOrder(Node* t);
    void postOrder();

};

#endif // TREE_H

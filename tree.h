#include <QApplication>
#ifndef TREE_H
#define TREE_H
#define MAX 1000
#include "qlist.h"
#include "qvector.h"
class Node
{
public:
    int id;
    QString tag;
    QString data;

    QVector<Node*> childern;
    Node(int id , QString tag , QString data);
    ~Node();

};

class Tree
{
private:
    Node* root;
public:
    Tree();
    ~Tree();
    void insert (Node* leaf , int id , QString tag , QString data, int parent);
    void insert(int id , QString tag , QString data, int parent);
    void postOrder(Node* t);
    void postOrder();

};

#endif // TREE_H

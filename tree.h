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
    int level;
    QVector<Node*> childern;

    QVector<QString> attrTag;
    QVector<QString> attrVal;

    Node(int id , QString tag , QString data, QVector<QString> attrTag , QVector<QString> attrVal , int level);
    ~Node();

};

class Tree
{
private:
    Node* root;
public:
    Tree();
    ~Tree();
    void insert (Node* leaf , int id , QString tag , QString data, QVector<QString> attrTag , QVector<QString> attrVal, int parent, int order);
    void insert(int id , QString tag , QString data, QVector<QString> attrTag , QVector<QString> attrVal , int parent, int order);
    void postOrder(Node* t);
    void postOrderMini(Node *t);
    void postOrder();
    void postOrderMini();

    void postOrderJson(Node *t);
    void postOrderJson();


};

#endif // TREE_H

#include "tree.h"
#include "QDebug"
Node::Node(int val)
{
        data = val;
}

Node::~Node()
{
    delete this;
    for ( int i = MAX ; i > 0 ; i++ )
    childern.clear();
}



Tree::Tree()
{
    root = NULL;
}

Tree::~Tree()
{
    for ( int i = 0 ; i < root->childern.size() ; i++ )
    {
        delete root->childern[i];
    }
    delete [] root;
}

void Tree::insert (Node* leaf , int val, int parent)
{


    Node* n = new Node(val);

    if(leaf->data == parent)
        leaf->childern.push_back(n);
    else
    {
        for(int i = 0 ; i < leaf->childern.size(); i++)
            insert(leaf->childern[i],val,parent);
    }
}

void Tree::insert(int val,int parent)
{
    if(root != NULL)
        insert(root,val,parent);

    else
    {
        root = new Node(val);
    }
}


void Tree::postOrder(Node* t)
    {
        if ( t  != NULL )
        {
            qDebug()<<t->data<<" ";

            for ( int i = 0 ; i < t->childern.size() ; i++)
            {
                postOrder(t->childern[i]);
            }
        }
    }

void Tree::postOrder()
    {
        postOrder(root);
    }

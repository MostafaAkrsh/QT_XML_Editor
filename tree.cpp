#include "tree.h"
#include "QDebug"
#include <QTextStream>
#include "global_objects.h"
Node::Node(int i , QString t , QString d)
{
        id = i;
        tag = t;
        data = d;
}

Node::~Node()
{
    for ( int i = 0 ; i < childern.size() ; i++ )
    {
        delete childern[i];
    }
    delete this;
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

void Tree::insert (Node* leaf , int id , QString tag , QString data, int parent)
{

    Node* n = new Node(id , tag , data);

    if(leaf->id == parent)
        leaf->childern.push_back(n);
    else
    {
        for(int i = 0 ; i < leaf->childern.size(); i++)
            insert(leaf->childern[i],id,tag,data,parent);
    }
}

void Tree::insert(int id , QString tag , QString data, int parent)
{
    if(root != NULL)
        insert(root,id,tag,data,parent);

    else
    {
        root = new Node(id,tag,data);
    }
}


void Tree::postOrder(Node* t)
    {
        if ( t  != NULL )
        {
         /*   for(int i = 0 ; i < t->id ; i++)
                xml+="\t";
*/
            xml +='<'+t->tag+'>';
            xml += "\n";
            if(t->data != NULL)
            xml +="\t" + t->data;
            else
            xml +=t->data;
            if(t->data != NULL)
                xml += "\n";
            for ( int i = 0 ; i < t->childern.size() ; i++)
            {
                postOrder(t->childern[i]);
            }
            xml += "</"+t->tag+'>'+"\n";
        }

        qDebug()<<xml;


    }

void Tree::postOrder()
    {
        postOrder(root);
    }

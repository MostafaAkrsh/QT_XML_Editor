#include "tree.h"

Node::Node(int val)
{
        data = val;
        for ( int i = 0 ; i < MAX ; i++ )
        {
            childern[i] = NULL;
        }
}

Node::~Node()
{
    delete this;
    for ( int i = MAX ; i > 0 ; i++ )
    {
        delete childern[i];
    }
}



Tree::Tree()
{

}

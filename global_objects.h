#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H
#include "QString"
#include "tree.h"
#include "QStack"

extern QString text;
extern QString xml;
extern QString fileName;
extern Tree t;
extern QStack<QString> s;

class global_objects
{
public:
    global_objects();
};

#endif // GLOBAL_OBJECTS_H

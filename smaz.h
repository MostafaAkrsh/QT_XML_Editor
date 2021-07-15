#ifndef SMAZ_H
#define SMAZ_H
#include <QApplication>
#include "qlist.h"
#include "qvector.h"

class smaz
{
public:    
    int smaz_compress(QString input, int inl, QString output, int outl);
    int smaz_decompress(QString input, int inl, QString output, int outl);
};

#endif // SMAZ_H

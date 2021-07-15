#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "QString"

class Compression
{
public:
    Compression();

   QString Compress(QString in);
   QString Decompress(QString in);



};

#endif // COMPRESSION_H

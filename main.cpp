#include "mainwindow.h"
#include "QDebug"
#include <QApplication>
#include "tree.h"
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Tree tree;

    tree.insert(1,"note","",0);
    tree.insert(1,"to","Tove",1);
    tree.insert(1,"from","Jani",1);
    tree.insert(1,"heading","Remainder",1);
    tree.insert(1,"body","Don't forget me this weekend!",1);

    tree.postOrder();

    return a.exec();



}

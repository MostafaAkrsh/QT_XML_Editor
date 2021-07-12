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

    tree.insert(2,0);
    tree.insert(5,2);
    tree.insert(3,2);
    tree.insert(6,5);
    tree.insert(11,6);
    tree.insert(40,3);

    tree.postOrder();

    return a.exec();



}

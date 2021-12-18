#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include "global_objects.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText(text);
    setWindowTitle(fileName);
}

Dialog::~Dialog()
{
    delete ui;
}

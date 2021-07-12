#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
bool tito = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openXML_PushButton_clicked()
{
    Dialog modalDialog;
    modalDialog.setModal(true);
    modalDialog.exec();
}


void MainWindow::on_browse_PushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

          // An object for reading and writing files
          QFile file(fileName);

          // Store the currentFile name
          currentFile = fileName;
          QString checkxml = fileName.right(3);

          // Try to open the file as a read only file if possible or display a
          // warning dialog box
          if (!file.open(QIODevice::ReadOnly | QFile::Text )|| !(checkxml == "xml" || checkxml =="XML")) {
              QMessageBox::warning(this, "Warning", "Cannot open file: please enter valid xml file");
              return;
          }

          QString e = fileName.right(20);

          // Set the title for the window to the file name
           ui->fileLabel->setText(e);
           ui->openXML_PushButton->setEnabled(1);
           ui->check_PushButton->setEnabled(1);

          // Interface for reading text
          QTextStream in(&file);
}


void MainWindow::on_check_PushButton_clicked()
{
    if(tito == true)
    {
        QMessageBox::information(this,"XML is consistent","GREAT! XML is already consistent");
        ui->process_PushButton->setEnabled(1);
        ui->format_PushButton->setEnabled(1);
        ui->minify_PushButton->setEnabled(1);

    }
    if(tito == false)
    {
        QMessageBox::warning(this, "XML is not consistent", "please, click [Fix XML] to fix it");
        ui->fix_PushButton->setEnabled(1);
    }

}


void MainWindow::on_fix_PushButton_clicked()
{
    QMessageBox::information(this,"XML has been fixed","XML has been fixed successfully!");
    ui->process_PushButton->setEnabled(1);
    ui->format_PushButton->setEnabled(1);
    ui->minify_PushButton->setEnabled(1);
}


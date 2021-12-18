#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"
#include "QDebug"
#include <QApplication>
#include "tree.h"
#include "global_objects.h"
#include "QStack"
#include "QMap"
#include "QDateTime"
#include "smaz.h"
#include "compression.h"

/* vectors to configure the visualization */
QVector<QString> attrT;
QVector<QTreeWidgetItem*> sons;

/* Setup the program window */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Setup the visualization */
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->header()->resizeSection(0,200);
    ui->treeWidget->header()->resizeSection(3,1000);
    ui->treeWidget->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Function to add a child in the visual xml tree */
void MainWindow::AddChild(QTreeWidgetItem* parent, QString tag , QVector<QString> attrTag, QVector<QString> attrVal, QString data )
{
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);

    QString at;

    if(attrTag.size() != 0)
        at += "[";

    for ( int i = 0 ; i < attrTag.size() ; i++ )
    {
        at += attrTag[i];

        if(i != attrTag.size() - 1) at+=" , ";
    }

    if(attrTag.size() != 0)
        at +="]";

    QString av= "";
    if(attrVal.size() != 0)
        av +="[";

    for ( int i = 0 ; i < attrVal.size() ; i++ )
    {
        av += attrVal[i];

        if(i != attrVal.size() - 1) av+=" , ";

    }

    if(attrVal.size() != 0)
        av +="]";


    itm->setText(0,tag);
    itm->setText(1,at);
    itm->setText(2,av);
    itm->setText(3,data);

    ui->treeWidget->addTopLevelItem(itm);

    sons.push_back(itm);
}

/* Function to open the secondaty open which display the content of the files */
void MainWindow::on_openXML_PushButton_clicked()
{
    text = xml;
    Dialog modalDialog;
    modalDialog.setModal(true);
    modalDialog.exec();
}


int flagConsistent = 0; // Flag to know if the xml is consistent of or not
int maxid = 0; // record the maximum id in the xml tree
int maxlevel = 0; // record the maximum depth level of the xml tree

/* After selecting the file do this operations */
void MainWindow::on_browse_PushButton_clicked()
{
    ui->treeWidget->hide(); // hide the tree widget

    t.~Tree(); // Destroy the previous tree

    ui->treeWidget->clear(); // Clear the tree widget
    sons.clear(); // Clear the content of sons vector
    AddChild(NULL,"root",attrT,attrT,""); // make the root for the tree

    /*Disable all the buttins */

    ui->openJSON_PushButton->setEnabled(0);
    ui->saveJSON_PushButton->setEnabled(0);
    ui->Visualize_PushButton->setEnabled(0);
    ui->format_PushButton->setEnabled(0);
    ui->minify_PushButton->setEnabled(0);
    ui->JSON_PushButton->setEnabled(0);

    /* info default strings */
    ui->nodesinfo->setText("???");
    ui->depthinfo->setText("???");

    /* Open the file dialog */
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile file(fileName);
    QFileInfo f(fileName);

    /* Set the data of the file */

    ui->dateinfo->setText(f.birthTime().toString("yyyy.MM.dd"));
    QString sI = QString::number(f.size());
    ui->sizeinfo->setText(sI+" Bytes");
    ui->ownerinfo->setText(f.lastModified().toString("yyyy.MM.dd"));
    ui->path_info->setText(f.path());
    ui->dateinfo_3->setText(f.lastRead().toString("yyyy.MM.dd"));


    currentFile = fileName;

    /* Check the xml extension */
    QString checkxml = fileName.right(3);


    if (!file.open(QIODevice::ReadOnly | QFile::Text )|| !(checkxml == "xml" || checkxml =="XML")) {
        QMessageBox::warning(this, "Warning", "Cannot open file: please enter valid xml file");
        return;
    }

    /* Take the name path of the file */
    QString e = fileName.right(20);

    /* Enable the buttons */
    ui->fileLabel->setText(e);
    ui->openXML_PushButton->setEnabled(1);
    ui->check_PushButton->setEnabled(1);
    ui->saveXML_PushButton->setEnabled(1);
    ui->CompressXML->setEnabled(1);
    ui->DecompressXML->setEnabled(1);

    /* copy the content of the file */
    QTextStream in(&file);

    /* take the text */
    text = in.readAll();
    xml = text;

    QString input = text;

    QString getstring;

    QVector<QString> att;
    QVector<QString> attval;

    /* the node data */
    int id = 1;
    int tag = 0;
    int level = 0;

    QStack<QString> s;
    QStack<int> parent; // stack to know the parent of the node
    parent.push(0); // add the root parent
    QMap<int,QString> mm;

    /* parsing the xml file */
    for ( int i = 0 ; i < input.size() ; i++ )
    {

        if( input[i]=='<' && input[i+1] !='/' && input[i+1] != '!' )
        {
            int first = 1;
            for ( int j = i ; j < input.size() ; j++ )
            {

                if(input[j] == ' ')
                {
                    if(first == 1)
                    {
                        tag = j - i;
                        first = 0;
                    }
                    for ( int l = j ; l < input.size() ; l++ )
                    {
                        if(input[l] == '=')
                        {
                            getstring = input.mid(j+1,l-j-1);
                            att.push_back(getstring);

                            for ( int k = l+2 ; k < input.size() ; k++ )
                            {
                                if (input[k] == '"')
                                {
                                    getstring = input.mid(l+2,k-l-2);
                                    attval.push_back(getstring);
                                    j = k;
                                    break;
                                }
                            }

                            break;
                        }

                    }

                }

                if ( input[j] == '>')
                {
                    QString data;

                    for(int q = j+1 ; q < input.size() ; q++ )
                    {
                        if(input[q] == '<' && input[q+1] != '/')
                            break;
                        if(input[q] == '<' && input[q+1] == '/')
                        {
                            getstring = input.mid(j+1,q-j-1);
                            data = getstring;
                            break;
                        }
                    }

                    if (first == 0)
                        getstring = input.mid(i+1,tag-1);
                    else
                        getstring = input.mid(i+1,j-i-1);



                    s.push(getstring);


                    AddChild(sons[parent.top()],getstring,att,attval,data);
                    t.insert(id,getstring,data,att,attval,parent.top(),level);
                    if (data == NULL)
                    {
                        level++;
                        if(level > maxlevel)
                            maxlevel = level;
                        parent.push(id);
                        mm[id] = getstring;
                    }
                    id++;
                    if(id > maxid)
                        maxid = id;
                    att.clear();
                    attval.clear();
                    break;
                }
            }
        }

        if(input[i]=='<' && input[i+1] =='/')
        {
            for ( int j = i ; j < input.size() ;j++ )
            {
                if ( input[j] == '>')
                {
                    if(j-i-2 > 0){
                        getstring = input.mid(i+2,j-i-2);
                        if (s.top() == getstring)
                        {
                            s.pop();
                            if(getstring == mm[parent.top()])
                            {
                                parent.pop();
                                level--;
                            }
                            break;
                        }
                    }
                }
            }



        }

        if(input[i]=='/' && input[i+1] =='>')
        {
            s.pop();

            parent.pop();

            level--;


        }
    }

    if(s.isEmpty()) flagConsistent = 1;
    else flagConsistent = 0;

    QString nI = QString::number(maxid - 1);

    ui->nodesinfo->setText(nI);

    QString dI = QString::number(maxlevel);

    ui->depthinfo->setText(dI);
}



/* Check the consistent of the XML file */
void MainWindow::on_check_PushButton_clicked()
{

    /* If file is consistent then enable the operation on the xml file*/
    if(flagConsistent == true)
    {
        QMessageBox::information(this,"XML is consistent","GREAT! XML is already consistent");
        ui->Visualize_PushButton->setEnabled(1);
        ui->format_PushButton->setEnabled(1);
        ui->minify_PushButton->setEnabled(1);
        ui->JSON_PushButton->setEnabled(1);


    }
    /* If the file is not consistent disable the operation and inform the user */
    else
    {
        QMessageBox::warning(this, "XML is not consistent", "please, click [Fix XML] to fix it");
        ui->fix_PushButton->setEnabled(1); // Enable the fix button
    }

}

/* Fix The XML File */
void MainWindow::on_fix_PushButton_clicked()
{
    /* This Feature will be implemented soon */

    QMessageBox::information(this,"Sorry","Sadly,This feature hasn't been implemented yet :`(");

}

/* Format The Xml File */
void MainWindow::on_format_PushButton_clicked()
{
    t.preOrder();
    text = xml;
    QMessageBox::information(this,"File has been formatted","XML is formatted successfully. Click [Open XML file] To show the effect");
}

/* Save XML File as file on file system */
void MainWindow::on_saveXML_PushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Output to file
    out << xml;
}

/* Minify The XML File */
void MainWindow::on_minify_PushButton_clicked()
{
    t.preOrderMini();
    text = xml;
    QMessageBox::information(this,"File has been minified","XML is minified successfully. Click [Open XML file] To show the effect");

}

/* Make JSON File  */
void MainWindow::on_JSON_PushButton_clicked()
{
    t.preOrderJson();
    QMessageBox::information(this,"Json File has been generated","Json file is generated successfully. Click [Open json file]");
    ui->openJSON_PushButton->setEnabled(1);
    ui->saveJSON_PushButton->setEnabled(1);
}

/* Open Json File */
void MainWindow::on_openJSON_PushButton_clicked()
{
    text = json;
    Dialog modalDialog;
    modalDialog.setModal(true);
    modalDialog.exec();
}


void MainWindow::on_saveJSON_PushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Output to file
    out << json;
}

/* Visualize the XML Tree */
void MainWindow::on_Visualize_PushButton_clicked()
{
    ui->treeWidget->show();

}

/* Compress The XML File */
void MainWindow::on_CompressXML_clicked()
{
    QString outy;
    Compression c;
    text = text.toLower();
    outy = c.Compress(text);

    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << outy;
}

/* Decompress The XML File */
void MainWindow::on_DecompressXML_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName);
    // Interface for reading text
    QTextStream in(&file);
    in.setCodec("UTF-8");

    // Copy text in the string
    QString texty = in.readAll();

    Compression c;

    texty = c.Decompress(texty);
    QString texty2 = texty;

    // Opens a dialog for saving a file
    QString fileName2 = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file2(fileName2);

    // Try to open a file with write only options
    if (!file2.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file2.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName2;

    // Set the title for the window to the file name
    setWindowTitle(fileName2);

    // Interface for writing text
    QTextStream out(&file2);
    out.setCodec("UTF-8");


    // Output to file
    out << texty;

}


void MainWindow::on_pushButton_20_clicked()
{
    int numm=rand() % 10 + 0;
    QString tany;
    tany.setNum(numm);
    QMessageBox::warning(this, "Warning", tany);

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtCore"
#include "QtGui"
#include "QTreeWidgetItem"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openXML_PushButton_clicked();

    void on_browse_PushButton_clicked();

    void on_check_PushButton_clicked();

    void on_fix_PushButton_clicked();

    void on_format_PushButton_clicked();

    void on_saveXML_PushButton_clicked();

    void on_minify_PushButton_clicked();

    void on_JSON_PushButton_clicked();

    void on_openJSON_PushButton_clicked();

    void on_saveJSON_PushButton_clicked();

    void on_Visualize_PushButton_clicked();

    void on_CompressXML_clicked();

    void on_DecompressXML_clicked();

    void on_pushButton_20_clicked();

public:
    void AddRoot(QString name, QString Description);
    void AddChild(QTreeWidgetItem* parent, QString tag , QVector<QString> attrTag, QVector<QString> attrVal, QString data );

private:
    Ui::MainWindow *ui;
    QString currentFile = "";

};
#endif // MAINWINDOW_H

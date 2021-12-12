#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<log_in.h>
#include<addmarket.h>
#include<ctrl_admin.h>


#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ctrl_admin ctrlAdmin;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void receiveData(QString data);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
